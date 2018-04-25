#include "v2v-following.hpp"



int main(){
    std::shared_ptr<V2VService> v2vService = std::make_shared<V2VService>();
    std::string groupId;
    std::cin >> groupId;
    while(1){
        if(!v2vService->connected){
            if(v2vService->following){
                v2vService->followRequest(v2vService->presentCars[groupId]);


            }
        }else {
            v2vService->followerStatus();
        }
        usleep(125000);
    }
}
