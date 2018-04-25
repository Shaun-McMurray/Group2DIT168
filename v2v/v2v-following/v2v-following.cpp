#include "v2v-following.hpp"



int main(){
    std::shared_ptr<V2VService> v2vService = std::make_shared<V2VService>();
    std::string groupId;
    std::cin >> groupId;
    bool start = false;
    while(1){
        if(!v2vService->connected){
            if(v2vService->following){
                v2vService->followRequest(v2vService->presentCars[groupId]);


            }
        }else {
            v2vService->followerStatus();
            if(start || v2vService->steeringQueue.size() >= 10 && v2vService->speed != 0){
                start = true;
                std::cout << "start = " << start << std::endl; 
                v2vService->steer(v2vService->steeringQueue.front());
                std::cout << "steering angle: " << v2vService->steeringQueue.front() << std::endl;
                v2vService->steeringQueue.pop();
            }
        }
        usleep(125000);
    }
}
