cmake_minimum_required(VERSION 3.2)
project(DIT168)
set(CMAKE_CXX_STANDARD 14)

find_package(libcluon REQUIRED)
find_package( OpenCV REQUIRED )
include_directories(SYSTEM ${CLUON_INCLUDE_DIRS})

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/messages.cpp
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   COMMAND cluon-msc --cpp-sources --cpp-add-include-file=messages.hpp --out=${CMAKE_BINARY_DIR}/messages.cpp ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd
                   COMMAND cluon-msc --cpp-headers --out=${CMAKE_BINARY_DIR}/messages.hpp ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd)
include_directories(SYSTEM ${CMAKE_BINARY_DIR})

add_executable(LaneDetection src/LaneDetection.cpp
${CMAKE_BINARY_DIR}/messages.cpp)
target_link_libraries(LaneDetection ${CLUON_LIBRARIES})
target_link_libraries( LaneDetection ${OpenCV_LIBS} )

if(FALSE) #commented out
include_directories(${DIT168_SOURCE_DIR}/src)
enable_testing()
add_executable(${PROJECT_NAME}-Runner test/TestPrimeChecker.cpp
src
src/PrimeChecker.cpp ${CMAKE_BINARY_DIR}/messages.cpp)
target_link_libraries(${PROJECT_NAME}-Runner ${CLUON_LIBRARIES})
add_test(NAME ${PROJECT_NAME}-Runner COMMAND ${PROJECT_NAME}-Runner)
endif()