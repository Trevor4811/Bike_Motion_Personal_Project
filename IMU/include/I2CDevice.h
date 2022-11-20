#ifndef _I2CDEVICE_H
#define _I2CDEVICE_H

#include <stdint.h>
#include <unistd.h>				
#include <fcntl.h>				
#include <sys/ioctl.h>	

#include "I2CBus.h"
//#include "LSM6DSOX.h"

/*!
 * @brief Class that represents communication with a general i2c slave device
 */
class I2CDevice {

    public:

    I2CDevice(const int slaveAddr);
    
    protected:

    int deviceFilenum;
    const int slaveAddress;

    uint8_t readRegister(uint16_t regAddress);
    uint8_t writeRegister(uint16_t regAddress, uint8_t val);

    private:

};


#endif
