#include "v2v-leading.hpp"
#include "OD4Conn.hpp"

int main(int argc, char **argv){

    std::shared_ptr<V2VService> v2vService = std::make_shared<V2VService>();
    // Getting dynamic IP
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
    
    std::shared_ptr<OD4Conn> connection = std::make_shared<OD4Conn>();
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
