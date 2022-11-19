
#include "../include/LSM6DSOX.h"

#include <iostream.h>

// Constructor that calls the device constructor
LSM6DSOX::LSM6DSOX(const int slaveAddr) : I2CDevice(slaveAddr) {
    if (verifyI2CAddr()) {
        //Error
        std::cout << "Failed to verify address. Actual: ";
        std::cout << std::hex << buf << "\n" << std::dec;
    } 

    std::cout << "Verified address\n";
    
}

int LSM6DSOX::readGyro(GyroData *gyroData) {
    gyroData->x = NaN;
    gyroData->y = NaN;
    gyroData->z = NaN;

    return 0;
}

int LSM6DSOX::readAccelerometer(AccelData *accelData) {
    accelData->x = NaN;
    accelData->y = NaN;
    accelData->z = NaN;

    return 0;
}

uint16_t LSM6DSOX::verifyI2CAddr() {
    uint16_t buf = 0;
    buf = i2c_smbus_read_word_data(deviceFilenum, RegisterAddress::LSM6DS_WHOAMI);

    if (buf != RegisterAddress::LSM6DSOX_CHIP_ID) {
        return buf;
    }
    return 0
}

int main(int argc, char **argv) {
    //int LSM6DSOX_ADRRESS = 0b110101;
    int LSM6DSOX_ADRRESS = 0x6a;
    //int LSM6DSOX_ADRRESS = 0x1c;
    LSM6DSOX imu(LSM6DSOX_ADRRESS);

    

}