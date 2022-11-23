#ifndef _LSM6DSOX_H
#define _LSM6DSOX_H

#define LSM6DS_I2CADDR_DEFAULT 0x6A ///< LSM6DS default i2c address

#include <iostream>

extern "C" {
    #include <linux/i2c-dev.h>
    #include <i2c/smbus.h>
}

#include "I2CDevice.h"

enum LSM6DSOXRegisterAddress {
    CHIP_ID = 0x6C,
	    
    FUNC_CFG_ACCESS = 0x1, ///< Enable embedded functions register
    INT1_CTRL = 0x0D,      ///< Interrupt control for INT 1
    INT2_CTRL = 0x0E,      ///< Interrupt control for INT 2
    WHOAMI = 0x0F,         ///< Chip ID register
    CTRL1_XL = 0x10,       ///< Main accelerometer config register
    CTRL2_G = 0x11,        ///< Main gyro config register
    CTRL3_C = 0x12,        ///< Main configuration register
    CTRL8_XL = 0x17,       ///< High and low pass for accel
    CTRL9_XL = 0x18, 	   ///< Accel settings 
    CTRL10_C = 0x19,       ///< Main configuration register
    WAKEUP_SRC = 0x1B,     ///< Why we woke up
    STATUS_REG = 0x1E,     ///< Status register
    OUT_TEMP_L = 0x20,     ///< First data register (temperature low)
    OUTX_L_G = 0x22,       ///< First gyro data register
    OUTX_L_A = 0x28,       ///< First accel data register
    STEPCOUNTER = 0x4B,    ///< 16-bit step counter
    TAP_CFG = 0x58        ///< Tap/pedometer configuration
};

typedef struct GyroData {
    uint16_t rawX;
    uint16_t rawy;
    uint16_t rawz;

    float x;
    float y;
    float z;
} GyroData;

typedef struct AccelData {
    uint16_t rawx;
    uint16_t rawy;
    uint16_t rawz;

    float x;
    float y;
    float z;
} AccelData;

/*!
 * @brief Class to control and communicate with the LSM6DSOX IMU
 */
class LSM6DSOX : public I2CDevice {

    public:

    /**
     * @brief Construct a new LSM6DSOX object
     * 
     */
    LSM6DSOX(const int slaveAddr);

    /*!
     * @brief Read the gyroscope data
     * 
     * @param gyroData pointer to the struct to store the gyro data in
     * @return int - Success returns 0
     */

    int readGyro(GyroData *gyroData);

    /*!
     * @brief Read the accelerometer data
     * 
     * @param accelData pointer to the struct to store the accelerometer data in
     * @return int - Success returns 0
     */
    int readAccelerometer(AccelData *accelData);

    private:

    uint16_t verifyI2CAddr();

    int setupDeviceParams();
    int setupAccel();
    int setupGyro();

    int swReset();

};

#endif
