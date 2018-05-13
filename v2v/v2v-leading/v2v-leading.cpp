#include "v2v-leading.hpp"
#include "OD4Conn.hpp"

int main(int argc, char **argv){

    std::shared_ptr<V2VService> v2vService = std::make_shared<V2VService>();
    // Getting dynamic IP, based off https://github.com/justasAtGU/v2v-protocol/blob/c26b113866f8ba4e00a5376e8996e06142c7e3b9/V2VService.cpp
    auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);

    // In case no IP or time diffrence is provided
    if (commandlineArguments.count("ip") == 0)
    {
        std::cerr << "You must specify your car's IP and the desired time to wait between status request" << std::endl;
        std::cerr << "Example: " << argv[0] << " --ip=120 " << std::endl;;
        return -1;
    }
    else
    {
        v2vService->setIp(commandlineArguments["ip"]);
    }

    //Creates an instance of the OD4Conn class that can be used to get the information from the last received message
    std::shared_ptr<OD4Conn> connection = std::make_shared<OD4Conn>();
    //A while-loop that sends announce presence until the car gets a follower and then sends leaderstatus every 125 milli seconds
    while(1){
        if(!v2vService->leading){
            //sends an announce presence message once every second
            v2vService->announcePresence();
            sleep(1);
      
        }else {
            //Sends the leader status message once every 125 milli seconds
            v2vService->leaderStatus(connection->getPedalPosition(), connection->getSteeringAngle(), connection->getDistanceTraveled());
            usleep(125000);
        }
    }
}
