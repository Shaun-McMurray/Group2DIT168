#include <messages.hpp>

/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */


uint32_t Message::ID() {
    return 1001;
}

const std::string Message::ShortName() {
    return "Message";
}
const std::string Message::LongName() {
    return "Message";
}

Message& Message::sMessage(const std::string &v) noexcept {
    m_sMessage = v;
    return *this;
}
std::string Message::sMessage() const noexcept {
    return m_sMessage;
}



