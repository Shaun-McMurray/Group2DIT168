
//Hough tranform parts source: http://www.transistor.io/revisiting-lane-detection-using-opencv.html

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

#define PI 3.1415926
const int MAX_KERNEL_LENGTH = 31;

void drawDetectedLines(Mat &image);
vector<Vec4i> findLines(Mat& binary);
Point drawIntersectionPunto(Mat &image, int tolerance);
int getCoord(int* dimCount, int dim, int tol);
bool getIntersectionPoint(cv::Point a1, cv::Point a2, cv::Point b1, cv::Point b2, cv::Point & intPnt);
double cross(Point v1, Point v2);

int minVote;
double minLength;
double maxGap;
vector<Vec4i> probLines;

//TODO: Warp image for birds eye view

int main() {

    cluon::OD4Session od4(130,[](cluon::data::Envelope &&envelope) noexcept {
       if(envelope.dataType() == 1112){
            CarControllerPedal receivedMsg = cluon::extractMessage<CarControllerPedal>(std::move(envelope));
        }else if(envelope.dataType() == 1113){
            CarControllerSteering receivedMsg = cluon::extractMessage<CarControllerSteering>(std::move(envelope));
        }
    });

    if(od4.isRunning() == 0){
        std::cout << "ERROR: No od4 running!!!" << std::endl;
        return -1;
    }

    int houghVote = 200;

    // Capture Input
    VideoCapture capture(0);

    if (!capture.isOpened()){
        std::cout << "ERROR: Can't start camera!!!" << std::endl;
        return -1;
    }

    capture.set(CV_CAP_PROP_POS_MSEC, 100000); //start the video at 100 seconds in

    Size frameSize(640, 480);

    Mat image;

    //Allow for PiCam to warm up, possibly not needed
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    while(1){
        
        //Take a frame
        capture >> image;

        if (image.empty())
            break;

        //Convert to grayscale
        Mat gray;
        cvtColor(image, gray, CV_RGB2GRAY);
        
        //Set bounds
        Rect roi(0, 0, 640, 480);
        Mat imgROI = image(roi);
        Scalar val = Scalar(0, 0, 0);
        copyMakeBorder(imgROI, imgROI, 2, 2, 2, 2, BORDER_CONSTANT, val);

        //Use Canny to find initial edges
        Mat contours;
        Canny(imgROI, contours, 100, 200);
        
        vector<Vec2f> lines;

        if(houghVote < 1 || lines.size() > 2){
            houghVote = 300;
        }else{
            houghVote += 25;
        }

        //Apply hough transfrom, multiple lines can be placed near each other
        //So 8 gets both sides covered
        while(lines.size() < 8 && houghVote > 0){
            HoughLines(contours, lines, 1, PI / 180, houghVote);
            houghVote -= 5;
        }


        // Draw the lines
        vector<Vec2f>::const_iterator i = lines.begin();
        Mat hough(imgROI.size(), CV_8U, Scalar(0));
        while (i != lines.end()) {

            float rho = (*i)[0];   // first element is distance rho
            float theta = (*i)[1]; // second element is angle theta

            if((theta > 0.09 && theta < 1.48) || (theta < 3.14 && theta > 1.66)){

                // point of intersection of the line with first row
                Point pt1(rho / cos(theta), 0);
                // point of intersection of the line with last row
                Point pt2((rho - hough.rows * sin(theta)) / cos(theta), hough.rows);
                // draw a line: Color = Scalar(R, G, B), thickness
                line(hough, pt1, pt2, Scalar(255, 255, 255), 1);
            }
            i++;
        }

        //Hough parameters
        minLength = 10; 
        maxGap = 60;
        minVote = 15; 

        //Hough Probabilistic to find lines
        vector<Vec4i> li = findLines(contours);
        Mat houghProbabilistic(imgROI.size(), CV_8U,Scalar(0));
        drawDetectedLines(houghProbabilistic);


        //Combine both images for accuraccy
        bitwise_and(houghProbabilistic, hough, houghProbabilistic);
        Mat houghPinv(imgROI.size(), CV_8U,Scalar(0));
        threshold(houghProbabilistic, houghPinv, 150, 255, THRESH_BINARY_INV);

        
        namedWindow("Detected Lines with Bitwise");
        imshow("Detected Lines with Bitwise", houghProbabilistic);
        


        Canny(houghPinv, contours, 100, 350);
        li = findLines(contours);

        //Stricter params for final lines
        minLength = 5;
        maxGap = 2;
        minVote = 1;
        
        //Final image
        drawDetectedLines(image);

        //Get point of intersection for steering
        Point iPnt = drawIntersectionPunto(image, 2);

        //TODO: filter out obviously wrong readings somtimes get


        //Finally calulate correct stering angle and send!
        if(iPnt.x != 0){

            float percentage = (float)iPnt.x / 640;
            float steering = (percentage * 90) - 45;
            opendlv::proxy::GroundSteeringReading msgSteering;
            msgSteering.steeringAngle(steering);
            od4.send(msgSteering);
            std::cout << "message sent: " <<  steering << std::endl;

            opendlv::proxy::PedalPositionReading msgPedal;
            msgPedal.percent(0.16);
            od4.send(msgPedal);

        }else{
            opendlv::proxy::GroundSteeringReading msgSteering;
            msgSteering.steeringAngle(0);
            od4.send(msgSteering);

            opendlv::proxy::PedalPositionReading msgPedal;
            msgPedal.percent(0.0);
            od4.send(msgPedal);
        }
        waitKey(1);
        lines.clear();
    }
}

//Helper functions: http://www.transistor.io/revisiting-lane-detection-using-opencv.html
vector<Vec4i> findLines(Mat& binary) {

    probLines.clear();
    HoughLinesP(binary, probLines, 1, PI /180, minVote, minLength, maxGap);
    

    for(size_t i = 0; i < probLines.size(); i++) {
        Vec4i l = probLines[i];
        Point p1, p2;
        p1 = Point(l[0], l[1]);
        p2 = Point(l[2], l[3]);

        //in radians
        float angle = atan2(p1.y - p2.y, p1.x - p2.x);
    }
    return probLines;
}

// Draw the detected lines on an image
void drawDetectedLines(Mat &image) {

    Scalar color = Scalar(200, 0, 100);
    vector<Vec4i>::const_iterator i = probLines.begin();

    while (i != probLines.end()) {

        Point pt1((*i)[0], (*i)[1]);
        Point pt2((*i)[2], (*i)[3]);

        line(image, pt1, pt2, color, 2);

        i++;
    }
}

Point drawIntersectionPunto(Mat &image, int tolerance){

    vector<Vec4i>::const_iterator i = probLines.begin();

    int cols = image.cols;
    int rows = image.rows;
    int intXCount[cols];
    int intYCount[rows];

    fill_n(intXCount, cols, 0);
    fill_n(intYCount, rows, 0);

    while(i != probLines.end()){

        Point pt1((*i)[0], (*i)[1]);
        Point pt2((*i)[2], (*i)[3]);

        vector<Vec4i>::const_iterator j = probLines.begin();

        while(j != probLines.end()){

            Point pt3((*j)[0], (*j)[1]);
            Point pt4((*j)[2], (*j)[3]);

            Point intPnt;
            bool intersect = getIntersectionPoint(pt1, pt2, pt3, pt4, intPnt);
            if(intersect){
                double theta1 = (*i)[1];
                double theta2 = (*j)[1];
                bool convergent = (theta1 > 1.48 && theta2 < 1.48) || (theta1 < 1.48 && theta2 > 1.48);
                if(convergent && intPnt.x < cols && intPnt.y < rows){
                    intXCount[intPnt.x] += 1;
                    intYCount[intPnt.y] += 1;
                }
            }
            j++;
        }
        i++;
    }

    cv::Point intersectPt;
    int x = getCoord(intXCount, cols, tolerance);
    int y = getCoord(intYCount, rows, tolerance);
    if(x != -1) {
        intersectPt.x = x;
        intersectPt.y = y;
    }
    return intersectPt;
}

int getCoord(int* dimCount, int dim, int tol) {
    int i, coordCount = 0, max = 0, coord = -1, j = 0;
    for(i = 0; i < dim; i++) {
        if(j == tol) {
            if(coordCount > max) {
                max = coordCount;
                coord = i + tol / 2;
            }
            coordCount = 0;
            j = 0;
        } else if(dimCount[i] != 0) {
            int c = dimCount[i];
            coordCount += c;
        }
        j++;
    }
    return coord;
}

bool getIntersectionPoint(Point a1, Point a2, Point b1, Point b2, Point & intPnt){
    Point p = a1;
    Point q = b1;
    Point r(a2 - a1);
    Point s(b2 - b1);

    if(cross(r, s) == 0){
        return false;
    }

    double t = cross(q - p, s) / cross(r, s);

    intPnt = p + t * r;

    return true;
}

double cross(Point v1, Point v2){
    return v1.x * v2.y - v1.y * v2.x;
}
