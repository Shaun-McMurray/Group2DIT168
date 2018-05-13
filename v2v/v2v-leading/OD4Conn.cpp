#include "OD4Conn.hpp"

/*
 Used to receive internal messages with information about pedal position, steering angle and distance traveled

*/

OD4Conn::OD4Conn() {
    broadcast =
        std::make_shared<cluon::OD4Session>(CHANNEL,
          [this](cluon::data::Envelope &&envelope) noexcept {
              std::cout << "[OD4] ";
              std::cout << envelope.dataType() << std::endl;
              switch(envelope.dataType()) {
                  case PEDAL_POSITION: {
                      opendlv::proxy::PedalPositionReading pp = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
                      OD4Conn::setPedalPosition(pp.percent());
                      }
                      break;
                  case STEERING_ANGLE:{
                      opendlv::proxy::GroundSteeringReading sa = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
                      OD4Conn::setSteeringAngle(sa.steeringAngle());
                      }
                      break;
                  case DISTANCE_TRAVELED:{
                      Distance_traveled da = cluon::extractMessage<Distance_traveled>(std::move(envelope));
                      OD4Conn::setDistanceTraveled(da.distanceTraveled());
                      }
                      break;
                  default:
                      break;
              }
    });
}

/*
 A setter for the pedal positon
*/

void OD4Conn::setPedalPosition(float pp){
    pedalPosition = pp;
}

/*
 A setter for the steering angle
*/

void OD4Conn::setSteeringAngle(float sa){
    steeringAngle = sa;
}

/*
 A setter for the distance traveled
*/
void OD4Conn::setDistanceTraveled(uint8_t dt){
    distanceTraveled = dt;
}

/*
 A getter for the pedal position
*/
float OD4Conn::getPedalPosition(){
    return pedalPosition;
}

/*
 A getter for the steering angle
*/
float OD4Conn::getSteeringAngle(){
    return steeringAngle;
}

/*
 A getter for the distance traveled
*/
uint8_t OD4Conn::getDistanceTraveled(){
    return distanceTraveled;
}

