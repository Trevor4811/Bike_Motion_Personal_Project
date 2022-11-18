#include <iostream>
#include <stdint.h>
#include <unistd.h>				
#include <fcntl.h>				
#include <sys/ioctl.h>	
// https://www.kernel.org/doc/Documentation/i2c/dev-interface 
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <stdio.h>
#include "../include/I2CDevice.h"
#include "../include/I2CBus.h"
#include "I2CBus.cpp"

// Public //

I2CDevice::I2CDevice(const int slaveAddr)  : slaveAddress(slaveAddr) {
    verifyI2CAddr();

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
    delete i2cFilenum;
}

// Protected //

// Private //

int I2CDevice::verifyI2CAddr() {
    return 0; 
}

int main(int argc, char **argv) {
    int LSM6DSOX_ADRRESS = 0b110101;
    //int LSM6DSOX_ADRRESS = 0x6a;
    I2CDevice device(LSM6DSOX_ADRRESS);

    

}
