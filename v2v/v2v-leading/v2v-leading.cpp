#include "v2v-leading.hpp"
int main(){
    std::shared_ptr<V2VService> v2vService = std::make_shared<V2VService>();
    float speed = 50;
    float angle = 0;
    unsigned int distance;
    while(1){
        if(!v2vService->leading){
            v2vService->announcePresence();
            sleep(1);
        }else {
            v2vService->leaderStatus(speed, angle, distance);
            usleep(125000);
        }
    }
}
