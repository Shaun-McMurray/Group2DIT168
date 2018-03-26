#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"

int main(){

    float command;
    CarControllerPedal pedalMsg;
    CarControllerSteering steeringMsg;

    std::clock_t start = std::clock();
    double duration;

    cluon::OD4Session od4(111,
        [](cluon::data::Envelope &&envelope) noexcept {});

    struct termios oldSettings, newSettings;

    tcgetattr( fileno( stdin ), &oldSettings );
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr( fileno( stdin ), TCSANOW, &newSettings );    

    while (1){

        fd_set set;
        struct timeval tv;

        tv.tv_sec = 10;
        tv.tv_usec = 0;

        FD_ZERO( &set );
        FD_SET( fileno( stdin ), &set );

        int res = select( fileno( stdin )+1, &set, NULL, NULL, &tv );

        if( res > 0 ){
            char c;
            read( fileno( stdin ), &c, 1 );

            std::cout << c << std::endl;

            duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

            if(duration > 0.01){

                switch(c){
                    case 'w':
                        command = 0.15;
                        std::cout << command << std::endl;
                        pedalMsg.pedal(command);
                        od4.send(pedalMsg);
                        break;
                    case 'a':
                        command = -15.0;
                        std::cout << command << std::endl;
                        steeringMsg.steering(command);
                        od4.send(steeringMsg);
                        break;
                    case 'd':
                        command = 15.0;
                        std::cout << command << std::endl;
                        steeringMsg.steering(command);
                        od4.send(steeringMsg);
                        break;
                    case 's':
                        command = -0.1;
                        std::cout << command << std::endl;
                        pedalMsg.pedal(command);
                        od4.send(pedalMsg);
                        break;
                    case 'q':
                        command = 0.0;
                        std::cout << command << std::endl;
                        steeringMsg.steering(command);
                        od4.send(steeringMsg);
                        break;
                    case 'e':
                        command = 0.0;
                        std::cout << command << std::endl;
                        pedalMsg.pedal(command);
                        od4.send(pedalMsg);
                        break;
                    default:
                       std::cout << "wrong input" << std::endl; 
                }

                start = std::clock();
            }
        }else if( res < 0 ){
            perror( "select error" );
            break;
        }else{
            printf( "Select timeout\n" );
        }
    }

    tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
    return 0;
}