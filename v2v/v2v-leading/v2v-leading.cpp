#include "v2v-leading.hpp"
#include "OD4Conn.hpp"

int main(){
   
    std::shared_ptr<V2VService> v2vService = std::make_shared<V2VService>();
    std::shared_ptr<OD4Conn> connection = std::make_shared<OD4Conn>();
    std::cout << "starting" << std::endl;
     while(1){
        if(!v2vService->leading){
            v2vService->announcePresence();
            sleep(1);
        }else {
            std::move(connection);
            v2vService->leaderStatus(connection->getPedalPosition(), connection->getSteeringAngle(), connection->getDistanceTraveled());
            usleep(125000);
        }
    }
}
