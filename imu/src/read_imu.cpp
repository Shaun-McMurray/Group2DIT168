#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include <cstdio>
#include <ctime>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"
//including libraries written in C
extern "C"
{
#include <roboticscape.h>
#include <rc_usefulincludes.h>
}
//commenting out
/*
//imu config struct
typedef struct rc_imu_config_t{
	// full scale ranges for sensors
	rc_accel_fsr_t accel_fsr; // AFS_2G, AFS_4G, AFS_8G, AFS_16G
	rc_gyro_fsr_t gyro_fsr;  // GFS_250,GFS_500,GFS_1000,GFS_2000
	
	// internal low pass filter constants
	rc_gyro_dlpf_t gyro_dlpf;
	rc_accel_dlpf_t accel_dlpf;
	
	// magnetometer use is optional 
	int enable_magnetometer; // 0 or 1
} rc_imu_config_t;

//imu data struct 
typedef struct rc_imu_data_t{
	// last read sensor values in real units
	float accel[3];	// units of m/s^2
	float gyro[3];	// units of degrees/s
	float mag[3];	// units of uT
	float temp;		// units of degrees Celsius
	
	// 16 bit raw adc readings from each sensor
	int16_t raw_gyro[3];	
	int16_t raw_accel[3];
	
	// FSR-derived conversion ratios from raw to real units
	float accel_to_ms2;	// to m/s^2
	float gyro_to_degs;	// to degrees/s
} rc_imu_data_t;
*/
int main(){
	rc_imu_data_t data;
	//initialize rc library
	std::cout << "Initializing roboticscape library.." << std::endl;
	if(rc_initialize()){
	 	std::cout << "ERROR: failed to initialize rc_initialize(), are you root?" << std::endl;
	  	return -1;
	 }

	rc_imu_config_t config = rc_default_imu_config();
	//calibrate gyroscope
	rc_is_gyro_calibrated();

	//initialize imu
	if(rc_initialize_imu(&data, config)){
        	std::cout << "rc_initialize_imu_failed"<< std::endl;
        	return -1;
    	}
    //create od4 session 
    cluon::OD4Session od4{130};
	while(od4.isRunning()){
		// read accelerometer sensor data
		if(rc_read_accel_data(&data)<0)
			std::cout << "read accel data failed"<< std::endl;

		//print the values directly
		std::cout << "Accelerometer values"<< std::endl;
		printf("%6.2f %6.2f %6.2f\n",data.accel[0],data.accel[1],data.accel[2]);
		accelerometerValues accelValues;
		accelValues.acceldata0(data.accel[0]);
		accelValues.acceldata1(data.accel[1]);
		accelValues.acceldata2(data.accel[2]);

		//send the values through od4
		od4.send(accelValues);

		//store values in variables for easier future filtering
		float accel_x = data.accel[0];
		float accel_y = data.accel[1];
		float accel_z = data.accel[2];

		//removing noise
		if(accel_x<0.2 && accel_x>0.1)
			accel_x = 0.0;

		if(accel_y<0.5 && accel_y>0.1)
			accel_y = 0.0;

		std::cout << "filtered data"<< std::endl;
		std::cout << accel_x << ", " << accel_y << ", " << accel_z << std::endl;

		//read gyroscope sensor data
		if(rc_read_gyro_data(&data)<0)
			std::cout << "read gyro data failed"<< std::endl;

		std::cout << "Gyro values in radians"<< std::endl;
		printf("%6.1f %6.1f %6.1f\n",data.gyro[0]*DEG_TO_RAD,\
									 data.gyro[1]*DEG_TO_RAD,\
									 data.gyro[2]*DEG_TO_RAD);

		std::cout << "gyro values in degrees"<< std::endl;

		printf("%6.1f %6.1f %6.1f\n",data.gyro[0],\
									 data.gyro[1],\
									 data.gyro[2]);

		//send gyro values through od4 session
		gyroscopeValues gyroValues;
		gyroValues.gyrodata0(data.gyro[0]);
		gyroValues.gyrodata1(data.gyro[1]);
		gyroValues.gyrodata2(data.gyro[2]);
		od4.send(gyroValues);
	}
	
	//rc_read_gyro_data(imu_data_t* data);
	rc_power_off_imu();
	//rc_i2c_release_bus(BUS);
 	rc_cleanup();
 	return 0;
	}
