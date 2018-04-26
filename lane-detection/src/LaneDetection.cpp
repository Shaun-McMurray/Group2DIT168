#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);

    waitKey(0);

    cluon::OD4Session od4(111,[](cluon::data::Envelope &&envelope) noexcept {
       if(envelope.dataType() == 1112){
            CarControllerPedal receivedMsg = cluon::extractMessage<CarControllerPedal>(std::move(envelope));
        }else if(envelope.dataType() == 1113){
            CarControllerSteering receivedMsg = cluon::extractMessage<CarControllerSteering>(std::move(envelope));
        }
    });
    return 0;
}
