#include "v2v-following.hpp"



int main(){
    std::shared_ptr<V2VService> v2vService = std::make_shared<V2VService>();
    controllerconnection =
        std::make_shared<cluon::OD4Session>(BROADCAST_CHANNEL,
          [](cluon::data::Envelope &&envelope) noexcept {});
    while(1){
        if(!v2vService->connected){
            if(v2vService->following){
                v2vService->followRequest(v2vService->presentCars["1"]);


            } else {


            }
        }else{
        //TODO send message from here
            //v2vService->speed
            //v2vService->steeringAngle
            //v2vService->distanceTraveled

        }
        usleep(125000);
    }
}

void v2v-following::pedal(float pedalPosition){
    if(!v2vService->followerIp.empty()) return;
    CarControllerPedal carControllerPedal;
    carControllerPedal.pedal(pedalPosition);
    controllerconnection->send(encode(carControllerPedal));
}
void v2v-following::steer(float steeringAngle){
    if(!v2vService->followerIp.empty()) return;
    CarControllerSteering carControllerSteering;
    carControllerSteering.steering(steeringAngle);
    controllerconnection->send(encode(carControllerSteering));
}

