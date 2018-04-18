#include "OD4Conn.hpp"


OD4Conn::OD4Conn() {
    broadcast =
        std::make_shared<cluon::OD4Session>(CHANNEL,
          [this](cluon::data::Envelope &&envelope) noexcept {
              std::cout << "[OD4] ";
              std::cout << envelope.dataType() << std::endl;
              switch(envelope.dataType()) {
                  case PEDAL_POSITION: {
                      std::cout << "test0" << std::endl;
                      Pedal_position pp = cluon::extractMessage<Pedal_position>(std::move(envelope));
                      OD4Conn::setPedalPosition(pp.speed());
                      std::cout << "test1" << std::endl;
                      }
                      break;
                  case STEERING_ANGLE:{
                      Steering_angle sa = cluon::extractMessage<Steering_angle>(std::move(envelope));
                      OD4Conn::setSteeringAngle(sa.steeringAngle());
                      std::cout << "test2" << std::endl;
                      }
                      break;
                  case DISTANCE_TRAVELED:{
                      Distance_traveled da = cluon::extractMessage<Distance_traveled>(std::move(envelope));
                      OD4Conn::setDistanceTraveled(da.distanceTraveled());
                      std::cout << "test3" << std::endl;
                      }
                      break;
                  default:
                      break;
              }
    });
}  

void OD4Conn::setPedalPosition(float pp){
    pedalPosition = pp;
}

void OD4Conn::setSteeringAngle(float sa){
    steeringAngle = sa;  
}

void OD4Conn::setDistanceTraveled(uint8_t dt){
    distanceTraveled = dt;
}

float OD4Conn::getPedalPosition(){
    return pedalPosition;
}

float OD4Conn::getSteeringAngle(){
    return steeringAngle;
}

uint8_t OD4Conn::getDistanceTraveled(){
    return distanceTraveled;
}

