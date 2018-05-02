cmake_minimum_required(VERSION 3.2)
project(imu_sensor)
set(CMAKE_CXX_STANDARD 14)

#find_package(libcluon REQUIRED)
#include_directories(SYSTEM ${CLUON_INCLUDE_DIRS})

################################################################################
# Defining the relevant versions of OpenDLV Standard Message Set and libcluon.
set(OPENDLV_STANDARD_MESSAGE_SET messages.odvd)
set(CLUON_COMPLETE cluon-complete.hpp)
################################################################################

link_directories(/etc/roboticscape)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/read_imu.cpp)

target_link_libraries(${PROJECT_NAME} roboticscape)
target_link_libraries(${PROJECT_NAME} ${CLUON_LIBRARIES})
add_library(roboticscape SHARED IMPORTED)
set_property(TARGET roboticscape PROPERTY IMPORTED_LOCATION "/usr/lib/libroboticscape.so")