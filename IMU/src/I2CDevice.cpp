#include <iostream>
#include <stdint.h>
#include <unistd.h>				
#include <fcntl.h>				
#include <sys/ioctl.h>	
// https://www.kernel.org/doc/Documentation/i2c/dev-interface 
extern "C" {
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
}
#include <stdio.h>
#include "../include/I2CDevice.h"
#include "../include/I2CBus.h"
#include "I2CBus.cpp"
#include "../include/LSM6DSOX.h"

// Public //

I2CDevice::I2CDevice(const int slaveAddr)  : slaveAddress(slaveAddr) {

    I2CBus bus;
    int *i2cFilenum = bus.openI2CBus();
    //int *i2cFilenum = open("/dev/i2c-1", O_RDWR); 
    std::cout << "I2C Bus:" << *i2cFilenum << "\n";

    int val = ioctl(*i2cFilenum, I2C_SLAVE, slaveAddress);
    if (val < 0) {
        /* ERROR HANDLING; you can check errno to see what went wrong */
    	std::cout << "Bad ioctl:" << val << "\t" << slaveAddress << "\n";
        perror("error");
    } else {
        std::cout << "Successfully addressed device\n";
    }

    uint16_t buf = 0;
    buf = i2c_smbus_read_word_data(*i2cFilenum, RegisterAddress::LSM6DS_WHOAMI);
    std::cout << std::hex << buf << "\t" << RegisterAddress::LSM6DSOX_CHIP_ID << "\n" << std::dec;

    verifyI2CAddr();
    
    delete i2cFilenum;
}

// Protected //

// Private //

int I2CDevice::verifyI2CAddr() {
    return 0; 
}

int main(int argc, char **argv) {
    //int LSM6DSOX_ADRRESS = 0b110101;
    int LSM6DSOX_ADRRESS = 0x6a;
    //int LSM6DSOX_ADRRESS = 0x1c;
    I2CDevice device(LSM6DSOX_ADRRESS);

    

}
