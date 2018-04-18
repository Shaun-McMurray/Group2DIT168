#ifndef OD4CONN_H
#define OD4CONN_H

#include "Messages.hpp"
#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"	
#include <iostream>
//#include "V2VService.hpp"

static const int CHANNEL = 30;
static const int PEDAL_POSITION = 9001;
static const int STEERING_ANGLE = 9002;
static const int DISTANCE_TRAVELED = 9003;

class OD4Conn {
public:
    OD4Conn();
    std::map <std::string, std::string> presentCars;
    void setPedalPosition(float pp);
    void setSteeringAngle(float sa);
    void setDistanceTraveled(uint8_t dt);

    float getPedalPosition();
    float getSteeringAngle();
    uint8_t getDistanceTraveled();

private:
    float pedalPosition = 0;
    float steeringAngle = 0;
    uint8_t distanceTraveled = 0;
std::shared_ptr<cluon::OD4Session>  broadcast;



};





#endif
