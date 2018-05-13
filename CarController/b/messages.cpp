#include <messages.hpp>

/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */


int32_t Message::ID() {
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



#include <messages.hpp>

/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */
namespace opendlv { namespace proxy {

int32_t GroundSteeringReading::ID() {
    return 1045;
}

const std::string GroundSteeringReading::ShortName() {
    return "GroundSteeringReading";
}
const std::string GroundSteeringReading::LongName() {
    return "opendlv.proxy.GroundSteeringReading";
}

GroundSteeringReading& GroundSteeringReading::steeringAngle(const float &v) noexcept {
    m_steeringAngle = v;
    return *this;
}
float GroundSteeringReading::steeringAngle() const noexcept {
    return m_steeringAngle;
}

}}

#include <messages.hpp>

/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */
namespace opendlv { namespace proxy {

int32_t PedalPositionReading::ID() {
    return 1041;
}

const std::string PedalPositionReading::ShortName() {
    return "PedalPositionReading";
}
const std::string PedalPositionReading::LongName() {
    return "opendlv.proxy.PedalPositionReading";
}

PedalPositionReading& PedalPositionReading::percent(const float &v) noexcept {
    m_percent = v;
    return *this;
}
float PedalPositionReading::percent() const noexcept {
    return m_percent;
}

}}

#include <messages.hpp>

/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */


int32_t CarControllerPedal::ID() {
    return 1002;
}

const std::string CarControllerPedal::ShortName() {
    return "CarControllerPedal";
}
const std::string CarControllerPedal::LongName() {
    return "CarControllerPedal";
}

CarControllerPedal& CarControllerPedal::pedal(const float &v) noexcept {
    m_pedal = v;
    return *this;
}
float CarControllerPedal::pedal() const noexcept {
    return m_pedal;
}



#include <messages.hpp>

/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */


int32_t CarControllerSteering::ID() {
    return 1003;
}

const std::string CarControllerSteering::ShortName() {
    return "CarControllerSteering";
}
const std::string CarControllerSteering::LongName() {
    return "CarControllerSteering";
}

CarControllerSteering& CarControllerSteering::steering(const float &v) noexcept {
    m_steering = v;
    return *this;
}
float CarControllerSteering::steering() const noexcept {
    return m_steering;
}



