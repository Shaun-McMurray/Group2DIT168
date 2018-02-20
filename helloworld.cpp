#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "PrimeChecker.hpp"
#include "messages.hpp"

typedef std::basic_string<char> string;

int main(int /*argc*/, char** /*argv*/) {
    //PrimeChecker pc;
    //std::cout << "Hello World = " << pc.isPrime(43) << std::endl;

    cluon::OD4Session od4(111,
        [](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == 1001) {
          Message receivedMsg = cluon::extractMessage<Message>(std::move(envelope));

          //PrimeChecker pc;
          std::cout << receivedMsg.sMessage() << std::endl;//" is " << (pc.isPrime(receivedMsg.sMessage()) ? "" : "not") << " a prime." << std::endl;
        }
    });

    while(1){}
   // string value;
    //std::cout << "Enter a number to check: ";
    //std::cin >> value;
    //Message msg;
    //msg.sMessage(value);

    //od4.send(msg);
    return 0;
}
