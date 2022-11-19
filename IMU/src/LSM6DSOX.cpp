
#include "../include/LSM6DSOX.h"


// Constructor that calls the device constructor
LSM6DSOX::LSM6DSOX(const int slaveAddr) : I2CDevice(slaveAddr) {
    
    uint16_t returnVal = verifyI2CAddr();
    if (returnVal) {
        //Error
	std::cout << "Failed to verify address. Actual: ";
        std::cout << std::hex << returnVal << "\n" << std::dec;
    	return;
    } 

    std::cout << "Verified address\n";
    
}

int LSM6DSOX::readGyro(GyroData *gyroData) {
    gyroData->x = 0;
    gyroData->y = 0;
    gyroData->z = 0;

    uint16_t temp = readRegister(LSM6DSOXRegisterAddress::STATUS_REG);
    temp = (temp << 1) & 1;
    std::cout << "gyro: " << temp << "\n";

    return temp;
}

int LSM6DSOX::readAccelerometer(AccelData *accelData) {
    accelData->x = 0;
    accelData->y = 0;
    accelData->z = 0;

    return 0;
}

uint16_t LSM6DSOX::verifyI2CAddr() {
    uint16_t buf = 0;
    buf = i2c_smbus_read_word_data(deviceFilenum, LSM6DSOXRegisterAddress::WHOAMI);

    if (buf != LSM6DSOXRegisterAddress::CHIP_ID) {
        return buf;
    }
    return 0;
}

int main(int argc, char **argv) {
    //int LSM6DSOX_ADRRESS = 0b110101;
    int IMU_ADRRESS = 0x6a;
    //int LSM6DSOX_ADRRESS = 0x1c;
    LSM6DSOX imu(LSM6DSOX_ADRRESS);

    

}
