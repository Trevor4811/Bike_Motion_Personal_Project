#include <iostream>
#include <stdint.h>
#include <unistd.h>				
#include <fcntl.h>				
#include <sys/ioctl.h>
#include <cmath>
// https://www.kernel.org/doc/Documentation/i2c/dev-interface 
extern "C" {
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
}
#include <stdio.h>
#include <bitset>
#include "../include/I2CDevice.h"

// Public //

I2CDevice::I2CDevice(const int slaveAddr) : slaveAddress(slaveAddr) {

    I2CBus bus;
    deviceFilenum = bus.openI2CBus();
    std::cout << "I2C Bus:" << deviceFilenum << "\n";

    if (ioctl(deviceFilenum, I2C_SLAVE, slaveAddress) < 0) {
        /* ERROR HANDLING; you can check errno to see what went wrong */
    	std::cout << "Bad ioctl to slave:" << slaveAddress << "\n";
        perror("error");
    } else {
        std::cout << "Successfully addressed device\n";
    }

}

// Protected //

uint8_t I2CDevice::readRegisterByte(uint16_t regAddress) {
    uint8_t buf = 0;
    buf = i2c_smbus_read_byte_data(deviceFilenum, regAddress);
    return buf;
}

uint8_t I2CDevice::writeRegisterByte(uint16_t regAddress, uint8_t val) {
    uint8_t buf = 0;
    buf = i2c_smbus_write_byte_data(deviceFilenum, regAddress, val);
    return buf;
}

// offset from the left, offset = 0 writes to the msb bit
int32_t I2CDevice::writeRegisterWordBitsMSBOffset(uint16_t regAddress, uint16_t val, uint8_t numBits, uint8_t offset) {
    uint8_t totalNumBits = 16;
    
    // check write overflow
    if (numBits + offset > totalNumBits) {
        return -1;
    }
    // bad offset
    if (offset < 0) {
        return -1;
    }

    // Get initial value
    uint16_t buf = i2c_smbus_read_word_data(deviceFilenum, regAddress);
    std::cout << "read = \t" << std::bitset<16>(buf) << "\n";

    // Mask bits being written to
    uint16_t ones = ~0;
    uint16_t mask = ones >> (totalNumBits-numBits);
    mask = mask << ((totalNumBits-numBits)-offset); // 00001100
    mask = ~mask; // 11110011
    buf = buf & mask;

    std::cout << "mask = \t" << std::bitset<16>(mask) << "\n";
    
    // write bits to offset location
    buf = buf | (val << ((totalNumBits-numBits)-offset));

    // Write new word data
    if (i2c_smbus_write_word_data(deviceFilenum, regAddress, buf)) {
        perror("Failed to write word data");
        return -1;
    }
    std::cout << "Buf: \t" << std::bitset<16>(buf) << "\n"; 
    return buf;
}

int16_t I2CDevice::writeRegisterByteBitsLSBOffset(uint16_t regAddress, uint8_t val, uint8_t numBits, uint8_t offset) {
    uint8_t totalNumBits = 8;
    
    // check offset
    if (offset > totalNumBits-1 || offset < 0) {
        return -1;
    }
    // check write overflow
    if (numBits > offset + 1) {
        return -1;
    }

    // Get initial value
    uint8_t buf = i2c_smbus_read_byte_data(deviceFilenum, regAddress);
    std::cout << "read = \t" << std::bitset<8>(buf) << "\n";

    // Mask bits being written to
    uint8_t ones = ~0;
    uint8_t mask = ones >> (totalNumBits-numBits);
    mask = mask << (offset-numBits+1); // 00110000
    mask = ~mask; // 11001111
    buf = buf & mask;

    std::cout << "mask = \t" << std::bitset<8>(mask) << "\n";

    // write bits to offset location
    buf = buf | (val << (offset-numBits+1));

    // Write new word data
    if (i2c_smbus_write_byte_data(deviceFilenum, regAddress, buf)) {
        perror("Failed to write word data");
        return -1;
    }
    std::cout << "Buf: \t" << std::bitset<8>(buf) << "\n";
    return buf;

}


uint8_t readRegisterByteBitsLSBOffset(uint16_t regAddresss, uint8_t numBits, uint8_t offset) {
    uint8_t totalNumBits = 8;
    
    // check offset
    if (offset > totalNumBits-1 || offset < 0) {
        return -1;
    }
    // check write overflow
    if (numBits > offset + 1) {
        return -1;
    }

    // Get initial value
    uint8_t buf = i2c_smbus_read_byte_data(deviceFilenum, regAddress);
    std::cout << "read = \t" << std::bitset<8>(buf) << "\n";

    // Shift bits to LSB
    buf = buf >> (offset-numBits+1);
    // Mask bits not being read
    uint8_t ones = ~0;
    uint8_t mask = ones >> (totalNumBits-numBits);
    buf = buf & mask;

    return buf;
}


// Private //

