#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"

int main(int /*argc*/, char** /*argv*/) {

    cluon::OD4Session od4(111,[](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
            //our message being delivered to ourselves
            opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
            std::cout << "Steering Angle: " << receivedMsg.steeringAngle() << std::endl;
        }
        else if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
            //our message being delivered to ourselves
            opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
            std::cout << "Speed percent:" << receivedMsg.percent() << std::endl;
        }
    });

    if(od4.isRunning() == 0)
    {
        std::cout << "ERROR: No od4 running!!!" << std::endl;
        return -1;
    }

    std::cout << "A new container has started" << std::endl;

    opendlv::proxy::GroundSteeringReading msgSteering;
    opendlv::proxy::PedalPositionReading msgPedal;

    const int delay = 1000;

    //Printout
    std::cout << "Forward straight" << std::endl;
    //send steering message to pwm component
    msgSteering.steeringAngle(0.0);
    od4.send(msgSteering);
    //send speed message to pwm component
    msgPedal.percent(0.15);
    od4.send(msgPedal);
    std::this_thread::sleep_for(std::chrono::milliseconds(2 * delay));

    std::cout << "Forward left" << std::endl;
    msgPedal.percent(0.15);
    od4.send(msgPedal);
    msgSteering.steeringAngle(-5);
    od4.send(msgSteering);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));

    std::cout << "Forward right" << std::endl;
    msgSteering.steeringAngle(5);
    od4.send(msgSteering);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));

    std::cout << "Forward straight" << std::endl;
    msgSteering.steeringAngle(0.0);
    od4.send(msgSteering);
    msgPedal.percent(0.15);
    od4.send(msgPedal);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));

    std::cout << "Finished" << std::endl;
    msgPedal.percent(0.0);
    od4.send(msgPedal);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));

    std::cout << "Now drive in a circle clockwise" << std::endl;
    msgSteering.steeringAngle(30.0);
    od4.send(msgSteering);
    msgPedal.percent(0.15);
    od4.send(msgPedal);
    std::this_thread::sleep_for(std::chrono::milliseconds(2 * delay));

    std::cout << "Now drive in a circle counter-clockwise" << std::endl;
    msgSteering.steeringAngle(-30.0);
    od4.send(msgSteering);
    msgPedal.percent(0.15);
    od4.send(msgPedal);
    std::this_thread::sleep_for(std::chrono::milliseconds(2 * delay));


    return 0;
}
