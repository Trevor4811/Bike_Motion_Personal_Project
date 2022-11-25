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
    
    /*! 
    * @brief Initialize an I2CDevice with the given slave address
    */
    I2CDevice(const int slaveAddr);
    
    protected:

    int deviceFilenum;
    const int slaveAddress;

    ////////////////
    // RegisterIO //
    ////////////////

    // Read little Endian 16 bit data starting at the given address into regValue
    // return 0 if successful
    int8_t readLittleEndian16BitData(uint16_t regAddress, uint16_t *regValue);

    // Read the 8-bit register and the register address
    int8_t readRegisterByte(uint16_t regAddress, uint8_t *regValue);
    
    // Write the given value to the 8-bit register at the register address
    uint8_t writeRegisterByte(uint16_t regAddress, uint8_t val);

    // Write the value to a 16-bit register starting at the given address.
    // The number of bits are written at the offset of the values msb from the registers msb.
    int32_t writeRegisterWordBitsMSBOffset(uint16_t regAddress, uint16_t val, uint8_t numBits, uint8_t offset);
    
    // Write the value to the 8-bit register with numBits being the number 
    // of bits to write and offset being the msb val bit in relation to the 
    // lsb of the register. Writing with offset 7 lines up the msb of the val 
    // with the msb of the register.
    // Returns the new 8-bit register value if successful and otherwise -1
    int16_t writeRegisterByteBitsLSBOffset(uint16_t regAddress, uint8_t val, uint8_t numBits, uint8_t offset);

    // Read the value of the 8-bit register with numBits being the number 
    // of bits to read and offset being the msb val bit in relation to the 
    // lsb of the register. Reading with offset 7 reads starting with the MSB
    // Returns the new 8-bit register value if successful and otherwise -1
    uint8_t readRegisterByteBitsLSBOffset(uint16_t regAddress, uint8_t numBits, uint8_t offset);


    private:

};


#endif
