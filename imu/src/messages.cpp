#include <messages.hpp>

/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */


int32_t accelerometerValues::ID() {
    return 2000;
}

const std::string accelerometerValues::ShortName() {
    return "accelerometerValues";
}
const std::string accelerometerValues::LongName() {
    return "accelerometerValues";
}

accelerometerValues& accelerometerValues::acceldata0(const float &v) noexcept {
    m_acceldata0 = v;
    return *this;
}
float accelerometerValues::acceldata0() const noexcept {
    return m_acceldata0;
}

accelerometerValues& accelerometerValues::acceldata1(const float &v) noexcept {
    m_acceldata1 = v;
    return *this;
}
float accelerometerValues::acceldata1() const noexcept {
    return m_acceldata1;
}

accelerometerValues& accelerometerValues::acceldata2(const float &v) noexcept {
    m_acceldata2 = v;
    return *this;
}
float accelerometerValues::acceldata2() const noexcept {
    return m_acceldata2;
}



#include <messages.hpp>

/*
 * THIS IS AN AUTO-GENERATED FILE. DO NOT MODIFY AS CHANGES MIGHT BE OVERWRITTEN!
 */


int32_t gyroscopeValues::ID() {
    return 2001;
}

const std::string gyroscopeValues::ShortName() {
    return "gyroscopeValues";
}
const std::string gyroscopeValues::LongName() {
    return "gyroscopeValues";
}

gyroscopeValues& gyroscopeValues::gyrodata0(const float &v) noexcept {
    m_gyrodata0 = v;
    return *this;
}
float gyroscopeValues::gyrodata0() const noexcept {
    return m_gyrodata0;
}

gyroscopeValues& gyroscopeValues::gyrodata1(const float &v) noexcept {
    m_gyrodata1 = v;
    return *this;
}
float gyroscopeValues::gyrodata1() const noexcept {
    return m_gyrodata1;
}

gyroscopeValues& gyroscopeValues::gyrodata2(const float &v) noexcept {
    m_gyrodata2 = v;
    return *this;
}
float gyroscopeValues::gyrodata2() const noexcept {
    return m_gyrodata2;
}



