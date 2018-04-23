#include "v2v-following.hpp"



int main(){
    std::shared_ptr<V2VService> v2vService = std::make_shared<V2VService>();
    std::shared_ptr<v2v_following> v2vFollow = std::make_shared<v2v_following>();
    std::shared_ptr<cluon::OD4Session> controllerconnection =
        std::make_shared<cluon::OD4Session>(CHANNEL,
          [](cluon::data::Envelope &&envelope) noexcept {});
    while(1){
        if(!v2vService->connected){
            if(v2vService->following){
                v2vService->followRequest(v2vService->presentCars["1"]);


            } else {


            }
        }else{
            v2vFollow->pedal(v2vService->speed);
            std::cout << v2vService->speed << " speed" << std::endl;
            v2vFollow->steer(v2vService->steeringAngle);
            std::cout << v2vService->steeringAngle << " steering" << std::endl;

            //TODO sometime
            //v2vService->distanceTraveled

        }
        usleep(125000);
    }
}

void v2v_following::pedal(float pedalPosition){
    opendlv::proxy::PedalPositionReading carPedal;
    carPedal.percent(pedalPosition);
    controllerconnection->send(carPedal);
}
void v2v_following::steer(float steeringAngle){
    opendlv::proxy::GroundSteeringReading carSteering;
    carSteering.steeringAngle(steeringAngle);
    controllerconnection->send(carSteering);
}
