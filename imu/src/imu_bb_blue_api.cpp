#include <iostream>
#include <chrono>
#include <thread>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"

extern "C"{
	#include <bb_blue_api.h>
}

int main(int /*argc*/, char** /*argv*/) {
	
	imu_data_t data; //struct to hold new data
	
	if(initialize_board()){
		std::cout << "ERROR: failed to initialize_cape." << std::endl;
		return -1;
	}
	
	// use defaults for now, except also enable magnetometer.
	imu_config_t conf = get_default_imu_config();
	conf.enable_magnetometer = 1;
	
	if(initialize_imu(&data, conf)){
		std::cout << "initialize_imu_failed" << std::endl;
		return -1;
	}
	
	// print a header
	std::cout << "   Accel XYZ(m/s^2)  |" << std::endl;
	std::cout << "   Gyro XYZ (deg/s)  |" << std::endl;
	std::cout << "  Mag Field XYZ(uT)  |" << std::endl;
	std::cout << " Temp (C)" << std::endl;
	
	//now just wait, print_data will run
	while (get_state() != EXITING) {

		if(read_accel_data(&data)<0){
			std::cout << "read accel data failed" << std::endl;
		}
		else {
			std::cout << data.accel[0] << ", " << data.accel[1] << ", " << data.accel[2] << std::endl;
		}					
		if(read_gyro_data(&data)<0){
			std::cout << "read gyro data failed" << std::endl;
		}
		else{
			std::cout << data.gyro[0] << ", " << data.gyro[1] << ", " << data.gyro[2] << std::endl;
		}					 
		if(read_mag_data(&data)<0){
			std::cout << "read mag data failed" << std::endl;
		}
		else {
			std::cout << data.mag[0] << ", " << data.mag[1] << ", " << data.mag[2] << std::endl;
		}						
		
		if(read_imu_temp(&data)<0){
			std::cout << "read temp data failed" << std::endl;
		}
		else{
			std::cout << data.temp << std::endl;
		}

		std::cout.flush();
		//usleep(100000);
		std::this_thread::sleep_for(std::chrono::milliseconds(x));
	}
	cleanup_board();
	return 0;
}
