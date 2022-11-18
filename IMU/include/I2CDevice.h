#ifndef _I2CDEVICE_H
#define _I2CDEVICE_H

#include <stdint.h>

#include <unistd.h>				
#include <fcntl.h>				
#include <sys/ioctl.h>	
// https://www.kernel.org/doc/Documentation/i2c/dev-interface 
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

/*!
 * @brief Class that represents communication with a general i2c slave device
 */
class I2CDevice {

    public:

    protected:

    I2CDevice(const int slaveAddr);

    int dataPin;
    int clockPin;
    uint8_t slaveAddress;

    int writeBuffer();
    int readBuffer();

    private:

};


#endif