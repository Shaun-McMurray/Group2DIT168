#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include <cstdio>
#include <ctime>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"

void sendPedalPositionReading(float pedal);
void sendGroundSteeringReading(float steering);
void stopWhenObstacle(float distance);

std::clock_t start;

int main(int /*argc*/, char** /*argv*/) {

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    cluon::OD4Session od4(130,[](cluon::data::Envelope &&envelope) noexcept {
       if(envelope.dataType() == 1002){
            CarControllerPedal receivedMsg = cluon::extractMessage<CarControllerPedal>(std::move(envelope));
            sendPedalPositionReading(receivedMsg.pedal());
            start = std::clock();
        }else if(envelope.dataType() == 1003){
            CarControllerSteering receivedMsg = cluon::extractMessage<CarControllerSteering>(std::move(envelope));
            sendGroundSteeringReading(receivedMsg.steering());
        }
    });

    //od4 with a separate CID for receiving messages from sensors when an obstacle has been detected in order to stop the car from moving
    cluon::OD4Session od4_stop(112,[](cluon::data::Envelope &&envelope) noexcept {
        if(envelope.dataType() == 1039){ 
            opendlv::proxy::DistanceReading receivedMsg = cluon::extractMessage<opendlv::proxy::DistanceReading>(std::move(envelope));
            stopWhenObstacle(receivedMsg.distance());
        }
    });

    if(od4.isRunning() == 0){
        std::cout << "ERROR: No od4 running!!!" << std::endl;
        return -1;
    } 

    double duration;
    opendlv::proxy::PedalPositionReading msgPedal;

    msgPedal.percent(0.2);
    od4.send(msgPedal);
    start = std::clock();

    while(1){
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        if(duration > 1){

            std::cout << "no input set speed to 0" << std::endl;
            msgPedal.percent(0.0);
            od4.send(msgPedal);
            start = std::clock(); 
        }
    }

    return 0;
}

//methods used to create new od4 sessions and send data to the od4 session at CID 130
void sendPedalPositionReading(float pedal){

    cluon::OD4Session od4(130,
        [](cluon::data::Envelope &&envelope) noexcept {});

    opendlv::proxy::PedalPositionReading msgPedal;
    msgPedal.percent(pedal);
    od4.send(msgPedal);
    start = std::clock();
} 

void sendGroundSteeringReading(float steering){

    cluon::OD4Session od4(130,
        [](cluon::data::Envelope &&envelope) noexcept {});

    opendlv::proxy::GroundSteeringReading msgSteering;
    msgSteering.steeringAngle(steering);
    od4.send(msgSteering);
}

void stopWhenObstacle(float distance){

    cluon::OD4Session od4(130,
        [](cluon::data::Envelope &&envelope) noexcept {});

    //std::cout << "Distance from obstacle is " << distance << " m." << std::endl;

    opendlv::proxy::PedalPositionReading msgPedal;
    msgPedal.percent(0.0);
    od4.send(msgPedal);
}
