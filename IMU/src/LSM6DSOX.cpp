
#include "../include/LSM6DSOX.h"
#include <bitset>
// Public //

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

    // setupAccel();
    setupGyro();
    
}

int LSM6DSOX::readGyro(GyroData *gyroData) {
    gyroData->x = 0;
    gyroData->y = 0;
    gyroData->z = 0;

    uint8_t temp = readRegisterByte(LSM6DSOXRegisterAddress::STATUS_REG);
    //temp = (temp << 1) & 1;
    std::cout << "Status: " << std::bitset<16>(temp) << "\n";
    
    temp = readRegisterByte(LSM6DSOXRegisterAddress::OUTX_L_G);
    //temp = (temp << 1) & 1;
    std::cout << "gyro: " << std::bitset<16>(temp) << "\n";

    temp = readRegisterByte(LSM6DSOXRegisterAddress::CTRL2_G);
    //temp = (temp << 1) & 1;
    std::cout << "gyro Settings: " << std::bitset<16>(temp) << "\n";


    return temp;
}

int LSM6DSOX::readAccelerometer(AccelData *accelData) {
    accelData->x = 0;
    accelData->y = 0;
    accelData->z = 0;

    return 0;
}

// Private //

uint16_t LSM6DSOX::verifyI2CAddr() {
    uint16_t buf = 0;
    buf = i2c_smbus_read_word_data(deviceFilenum, LSM6DSOXRegisterAddress::WHOAMI);

    if (buf != LSM6DSOXRegisterAddress::CHIP_ID) {
        return buf;
    }
    return 0;
}

int LSM6DSOX::setupAccel() {
    // Turn on the accelerometer
    writeRegisterWordBitsMSBOffset(LSM6DSOXRegisterAddress::INT1_CTRL, 1, 0b1, 8);

    // Set high performance mode (417 Hz)
    writeRegisterWordBitsMSBOffset(LSM6DSOXRegisterAddress::CTRL1_XL, 2, 0b11, 0);

    return 0;
}

int LSM6DSOX::setupGyro() {
    // Turn on the gyroscope
    std::cout << "INT1_CTRL: " << "\n";
    writeRegisterWordBitsMSBOffset(LSM6DSOXRegisterAddress::INT1_CTRL, 1, 0b1, 7);

    // Set high performance mode (417 Hz)
    std::cout << "CTRL2_G: " << "\n";
    writeRegisterWordBitsMSBOffset(LSM6DSOXRegisterAddress::CTRL2_G, 2, 0b11, 0);

    return 0;
}

int main(int argc, char **argv) {
    //int LSM6DSOX_ADRRESS = 0b110101;
    int IMU_ADRRESS = 0x6a;
    //int LSM6DSOX_ADRRESS = 0x1c;
    LSM6DSOX imu(IMU_ADRRESS);
    GyroData gd;

    for (int i = 0; i < 100000000; i++) {
    }
    imu.readGyro(&gd);


    

}
