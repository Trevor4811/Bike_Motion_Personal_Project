
#include "../include/LSM6DSOX.h"
#include <bitset>
#include <unistd.h>

// Public //

// Constructor that calls the device constructor
LSM6DSOX::LSM6DSOX(const int slaveAddr) : I2CDevice(slaveAddr) {
    
    uint16_t returnVal = verifyI2CAddr();
    if (returnVal) {
        //Error
	std::cout << "Failed to verify address. Actual: ";
        std::cout << std::hex << returnVal << "\n" << std::dec;
    	//return;
    } 

    std::cout << "Verified address\n";

    swReset();
    std::cout << "Reset LSM6DSOX\n";

    // setupAccel();
    setupDeviceParams();
    setupGyro();
    setupAccel();
    sleep(1);
}

int LSM6DSOX::readGyro(GyroData *gyroData) {
    // Check data available
    uint8_t status;
    readRegisterByte(LSM6DSOXRegisterAddress::STATUS_REG, &status);
    status = (status >> 1) & 1;
    if (!status) {
        std::cout << "No Gyro Data\n";
        return -1;
    }

    // read data x, y, z
    if (readLittleEndian16BitData(LSM6DSOXRegisterAddress::OUTX_L_G, &(gyroData->rawx))) {
        return -1;
    }
    if (readLittleEndian16BitData(LSM6DSOXRegisterAddress::OUTY_L_G, &(gyroData->rawy))) {
        return -1;
    }
    if (readLittleEndian16BitData(LSM6DSOXRegisterAddress::OUTZ_L_G, &(gyroData->rawz))) {
        return -1;
    }

    // convert raw 
    convertGyroData(gyroData);

    return 0;
}

int LSM6DSOX::readAccelerometer(AccelData *accelData) {

    // Check data available
    uint8_t status;
    readRegisterByte(LSM6DSOXRegisterAddress::STATUS_REG, &status);
    std::cout << "Status: " << std::bitset<8>(status) << "\n";
    status = status & 1;
    if (!status) {
        std::cout << "No Accel Data\n";
        return -1;
    }
   
    // read data x, y, z
    if (readLittleEndian16BitData(LSM6DSOXRegisterAddress::OUTX_L_A, &(accelData->rawx))) {
        return -1;
    }
    if (readLittleEndian16BitData(LSM6DSOXRegisterAddress::OUTY_L_A, &(accelData->rawy))) {
        return -1;
    }
    if (readLittleEndian16BitData(LSM6DSOXRegisterAddress::OUTZ_L_A, &(accelData->rawz))) {
        return -1;
    }

    // convert raw 
    convertAccelData(accelData);

    return 0;
}

// Private //

uint16_t LSM6DSOX::verifyI2CAddr() {
    uint8_t buf = 0;
    if (readRegisterByte(LSM6DSOXRegisterAddress::WHOAMI, &buf)) {
        return ~0;
    }
    std::cout << "Who am I return: " << std::bitset<8>(buf) << "\n";

    if (buf != LSM6DSOXRegisterAddress::CHIP_ID) {
        return buf;
    }
    return 0;
}

int LSM6DSOX::setupDeviceParams() {
    // Block Data Update
    std::cout << "CTRL3_C dev: " << "\n";
    writeRegisterByteBitsLSBOffset(LSM6DSOXRegisterAddress::CTRL3_C, 1, 1, 6);

    // Disable I3C
    std::cout << "CTRL9_XL dev" << "\n";
    writeRegisterByteBitsLSBOffset(LSM6DSOXRegisterAddress::CTRL9_XL, 1, 1, 1);

    return 0;
}

int LSM6DSOX::setupAccel() {
    // Turn on the accelerometer
    std::cout << "INT1_CTRL XL: " << "\n";
    writeRegisterByteBitsLSBOffset(LSM6DSOXRegisterAddress::INT1_CTRL, 1, 1, 0);

    // Set high performance mode (417 Hz)
    std::cout << "CTRL1_XL: " << "\n";
    writeRegisterByteBitsLSBOffset(LSM6DSOXRegisterAddress::CTRL1_XL, 4, 4, 7);

    return 0;
}

int LSM6DSOX::setupGyro() {
    // Turn on the gyroscope
    std::cout << "INT1_CTRL G: " << "\n";
    writeRegisterByteBitsLSBOffset(LSM6DSOXRegisterAddress::INT1_CTRL, 1, 1, 1);

    // Set high performance mode (417 Hz)
    std::cout << "CTRL2_G: " << "\n";
    writeRegisterByteBitsLSBOffset(LSM6DSOXRegisterAddress::CTRL2_G, 4, 4, 7);

    return 0;
}

int LSM6DSOX::swReset() {
    std::cout << "CTRL3_C: " << "\n";
    writeRegisterByteBitsLSBOffset(LSM6DSOXRegisterAddress::CTRL3_C, 1, 1, 0);

    uint8_t reset = 1; 
    while (reset) {
        reset = readRegisterByteBitsLSBOffset(LSM6DSOXRegisterAddress::CTRL3_C, 1, 0);
        sleep(1);
    }

    std::cout << "Completed LSM6DSOX software reset" << "\n";
    return 0;
}

void LSM6DSOX::convertAccelData(AccelData *accelData) {
    accelData->x = accelData->rawx;
    accelData->y = accelData->rawy;
    accelData->z = accelData->rawz;
}

void LSM6DSOX::convertGyroData(GyroData *gyroData) {
    gyroData->x = gyroData->rawx;
    gyroData->y = gyroData->rawy;
    gyroData->z = gyroData->rawz;
}

int main(int argc, char **argv) {
    //int LSM6DSOX_ADRRESS = 0b110101;
    int IMU_ADRRESS = 0x6a;
    //int LSM6DSOX_ADRRESS = 0x1c;
    LSM6DSOX imu(IMU_ADRRESS);
    GyroData gd;
    AccelData ad;

    for (int i = 0; i < 100; i++) {
	sleep(1);
        if (!imu.readAccelerometer(&ad)) {
            std::cout << "AccelData:\t" << ad.x << ", " << ad.y  << ", " << ad.z << "\n"; 
        }
        if (!imu.readGyro(&gd)) {
            std::cout << "GyroData:\t" << gd.x << ", " << gd.y  << ", " << gd.z << "\n"; 
        }
    }


    

}
