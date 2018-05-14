cmake_minimum_required(VERSION 3.2)
project(imu_sensor)
 #find_package(libcluon REQUIRED)
 #include_directories(SYSTEM ${CLUON_INCLUDE_DIRS})
################################################################################

# Defining the relevant versions of OpenDLV Standard Message Set and libcluon.
set(OPENDLV_STANDARD_MESSAGE_SET messages.odvd)
set(CLUON_COMPLETE cluon-complete.hpp)

################################################################################

# This project requires C++14 or newer.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Strip unneeded symbols from binaries.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
# Build a static binary.
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
# Threads are necessary for linking the resulting binaries as UDPReceiver is running in parallel.
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

################################################################################

link_directories(/etc/roboticscape)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/read_imu.cpp)

target_link_libraries(${PROJECT_NAME} roboticscape)
add_library(roboticscape SHARED IMPORTED)
set_property(TARGET roboticscape PROPERTY IMPORTED_LOCATION "/usr/lib/libroboticscape.so")
