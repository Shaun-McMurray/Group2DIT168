#ifndef V2V_FOLLOWING
#define V2V_FOLLOWING

#include "V2VService.hpp"

static const int CHANNEL = 130;

class v2v_following{
public:
    std::shared_ptr<V2VService> v2vService = std::make_shared<V2VService>();
    std::shared_ptr<v2v_following> v2vFollow = std::make_shared<v2v_following>();
    std::shared_ptr<cluon::OD4Session> controllerconnection;
    void pedal(float pedalPosition);
    void steer(float steeringAngle);

private:


};


#endif
