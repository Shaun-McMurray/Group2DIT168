cmake_minimum_required(VERSION 3.2)
project(sensors)
set(CMAKE_CXX_STANDARD 14)

link_directories(/etc/roboticscape)
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/read_sensor.cpp)
target_link_libraries(${PROJECT_NAME} ${CLUON_LIBRARIES} roboticscape)
add_library(roboticscape SHARED IMPORTED)
set_property(TARGET roboticscape PROPERTY IMPORTED_LOCATION "/usr/lib/libroboticscape.so")
