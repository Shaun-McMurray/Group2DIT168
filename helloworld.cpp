#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "PrimeChecker.hpp"
#include "messages.hpp"

int main(int /*argc*/, char** /*argv*/) {
    PrimeChecker pc;
    std::cout << "Hello World = " << pc.isPrime(43) << std::endl;

    cluon::OD4Session od4(111,
        [](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == 1001) {
          MyTestMessage1 receivedMsg = cluon::extractMessage<MyTestMessage1>(std::move(envelope));

          PrimeChecker pc;
          std::cout << receivedMsg.myValue() << " is " << (pc.isPrime(receivedMsg.myValue()) ? "" : "not") << " a prime." << std::endl;
        }
    });

    uint16_t value;
    std::cout << "Enter a number to check: ";
    std::cin >> value;
    MyTestMessage1 msg;
    msg.myValue(value);

    od4.send(msg);
    return 0;
}
