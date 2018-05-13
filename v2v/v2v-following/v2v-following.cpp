#include "v2v-following.hpp"

/*
This main is used for the v2v-following micro service, it needs a number to be used as the delay for the messages
and also a group id which is the group it will automatically connect to when it receives an announce presence from a group using that id 
*/
int main(){
    //Creates an instance of the V2VService
    std::shared_ptr<V2VService> v2vService = std::make_shared<V2VService>();
    
    //Asks for the number to be used for the delay and then saves it when it receives one
    std::cout << "input the number of messages to delay" << std::endl;
    std::cin >> v2vService->delay;
    
    //Asks for a group id and then saves it when it receives one
    std::string groupId;
    std::cout << "group id to follow" << std::endl;
    std::cin >> groupId;
    
    //Makes sure that the start boolean is set to false
    bool start = false;
    
    //This while-loop makes sure that the car automatically connects to the given group id and
    //also sends the follower status once every 125 milli seconds
    while(1){
        if(!v2vService->connected){
            
            //Sends a follow request when the an announce presence message with the correct group id is received
            if(v2vService->following){
                v2vService->followRequest(v2vService->presentCars[groupId]);


            }
        //When the car is following another car this else happens and sends a follower status once every 125 milli seconds
        }else {
            v2vService->followerStatus();
        }
        //Makes the loop sleep 125 milli seconds each loop to make sure that the time between messages are aproximately 125 milli seconds
        usleep(125000);
    }
}

