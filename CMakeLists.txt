cmake_minimum_required(VERSION 3.2)
project(DIT168)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wlogical-op -Wold-style-cast -Wuseless-cast -Wdouble-promotion -Wshadow -Wformat=2")

find_package(libcluon REQUIRED)
include_directories(SYSTEM ${CLUON_INCLUDE_DIRS})

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/messages.cpp
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   COMMAND cluon-msc --cpp-sources --cpp-add-include-file=messages.hpp --out=${CMAKE_BINARY_DIR}/messages.cpp ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd
                   COMMAND cluon-msc --cpp-headers --out=${CMAKE_BINARY_DIR}/messages.hpp ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd)
include_directories(SYSTEM ${CMAKE_BINARY_DIR})

add_executable(Recieve src/Recieve.cpp
${CMAKE_BINARY_DIR}/messages.cpp)
target_link_libraries(Recieve ${CLUON_LIBRARIES})

add_executable(Send src/Send.cpp
${CMAKE_BINARY_DIR}/messages.cpp)
target_link_libraries(Send ${CLUON_LIBRARIES})

include_directories(${DIT168_SOURCE_DIR}/src)
enable_testing()
add_executable(${PROJECT_NAME}-Runner test/TestPrimeChecker.cpp
src
src/PrimeChecker.cpp ${CMAKE_BINARY_DIR}/messages.cpp)
target_link_libraries(${PROJECT_NAME}-Runner ${CLUON_LIBRARIES})
add_test(NAME ${PROJECT_NAME}-Runner COMMAND ${PROJECT_NAME}-Runner)
