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

std::clock_t start;


int main(int /*argc*/, char** /*argv*/) {

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    cluon::OD4Session od4(111,[](cluon::data::Envelope &&envelope) noexcept {
       if(envelope.dataType() == 1002){
            CarControllerPedal receivedMsg = cluon::extractMessage<CarControllerPedal>(std::move(envelope));
            sendPedalPositionReading(receivedMsg.pedal());
            start = std::clock();
        }else if(envelope.dataType() == 1003){
            CarControllerSteering receivedMsg = cluon::extractMessage<CarControllerSteering>(std::move(envelope));
            sendGroundSteeringReading(receivedMsg.steering());
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

void sendPedalPositionReading(float pedal){

    cluon::OD4Session od4(111,
        [](cluon::data::Envelope &&envelope) noexcept {});

    opendlv::proxy::PedalPositionReading msgPedal;
    msgPedal.percent(pedal);
    od4.send(msgPedal);
    start = std::clock();
}

void sendGroundSteeringReading(float steering){

    cluon::OD4Session od4(111,
        [](cluon::data::Envelope &&envelope) noexcept {});

    opendlv::proxy::GroundSteeringReading msgSteering;
    msgSteering.steeringAngle(steering);
    od4.send(msgSteering);
}