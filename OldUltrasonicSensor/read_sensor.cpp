//include statements
#include <iostream>
#include <thread>

//including libraries written in C
extern "C"
{
#include <roboticscape.h>
#include <rc_usefulincludes.h>
}

//defining ports
#define BUS 1
#define FRONT_ADDR 0x70
#define BACK_ADDR 0x71

#define SOFTWARE_REVISION 0x00
#define FIRST_ECHO        0x03

#define COMMAND_REG       0x00
//centimeter distance
#define CM                0x51

//using namespace std;

int main(){
 int addr1 = 112; //0x70
 int addr2 = 113; //0x71

 uint8_t unit_byte = 0;
 uint8_t v_byte = 0;
 uint8_t act_byte = 0;
 uint8_t *data;

 //initialize library
 std::cout << "Initializing roboticscape library.." << std::endl;
 if(rc_initialize()){
  std::cout << "ERROR: failed to initialize rc_initialize(), are you root?\n" << std::endl;
  return -1;
 }

 //initialize bus
 std::cout << "Initializing bus.." << std::endl;
 if(rc_i2c_init(BUS, FRONT_ADDR)){
  std::cout << "ERROR: failed to initialize bus\n" << std::endl;
  return -1;
 }

 //rc_i2c_claim_bus(BUS);
 //trigger the sensor to store a cm reading in its register
 rc_i2c_write_byte(BUS, COMMAND_REG, CM);
 //printf("Here\n");
 //std::this_thread::sleep_for(0.005s);

 //rc_i2c_read_byte(BUS, SOFTWARE_REVISION, &v_byte);
 //printf("and here\n");

 while(v_byte != 11)
  rc_i2c_read_byte(BUS, SOFTWARE_REVISION, &v_byte);

 rc_i2c_read_byte(BUS, FIRST_ECHO, &unit_byte);
 printf("Reading %u cm\n", unit_byte);
 act_byte = unit_byte - 3;
 printf("Actual range is: %d \n", act_byte);
 if((rc_i2c_read_byte) < 0)
  fprintf(stderr,"\rERROR: Can't read Sensor");

 //rc_i2c_release_bus(BUS);
 rc_cleanup();
 return 0;
}

 //rc_i2c_release_bus(BUS);
 rc_cleanup();
 return 0;
}
