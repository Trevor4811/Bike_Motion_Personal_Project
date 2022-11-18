#include <iostream>
#include <stdint.h>
#include <unistd.h>				
#include <fcntl.h>				
#include <sys/ioctl.h>	
// https://www.kernel.org/doc/Documentation/i2c/dev-interface 
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

#include "../include/I2CDevice.h"
#include "../include/I2CBus.h"

// Public //

I2CDevice::I2CDevice(const int slaveAddr)  : slaveAddress(slaveAddr) {
    verifyI2CAddr()

    I2CBus bus;
    int *i2cFilenum = bus.openI2CBus();
    std::cout << "I2C Bus:" << *i2cFilenum << "\n";
    delete i2cFilenum;

    if (ioctl(file, I2C_SLAVE, slaveAddress) < 0) {
        /* ERROR HANDLING; you can check errno to see what went wrong */
        exit(1);
    }

    std::cout << "Successfully addressed device\n";
}

// Protected //

// Private //

I2CDevice::verifyI2CAddr() {
    
}

int main(int argc, char **argv) {
    int LSM6DSOX_ADRRESS = 110101xb
    I2CDevice::I2CDevice device(LSM6DSOX_ADRRESS);

    

}