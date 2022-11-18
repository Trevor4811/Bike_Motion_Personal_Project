
#include <stdint.h>

#include <unistd.h>				
#include <fcntl.h>				
#include <sys/ioctl.h>	
// https://www.kernel.org/doc/Documentation/i2c/dev-interface 
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

#include "../include/I2CDevice.h"

// Public //

I2CDevice::I2CDevice(const int slaveAddr)  : slaveAddress(slaveAddr) {
    verifyI2CAddr()
    int addr = 0x40; /* The I2C address */

    if (ioctl(file, I2C_SLAVE, addr) < 0) {
        /* ERROR HANDLING; you can check errno to see what went wrong */
        exit(1);
    }
}

// Protected //

// Private //

I2CDevice::verifyI2CAddr() {
    
}