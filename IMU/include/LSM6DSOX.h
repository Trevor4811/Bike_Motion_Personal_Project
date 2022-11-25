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
    OUTX_H_G = 0x23,       ///< First gyro data register
    OUTY_L_G = 0x24,       ///< First gyro data register
    OUTY_H_G = 0x25,       ///< First gyro data register
    OUTZ_L_G = 0x26,       ///< First gyro data register
    OUTZ_H_G = 0x27,       ///< First gyro data register
    
    OUTX_L_A = 0x28,       ///< First gyro data register
    OUTX_H_A = 0x29,       ///< First gyro data register
    OUTY_L_A = 0x2A,       ///< First gyro data register
    OUTY_H_A = 0x2B,       ///< First gyro data register
    OUTZ_L_A = 0x2C,       ///< First gyro data register
    OUTZ_H_A = 0x2D,       ///< First gyro data register
    
    STEPCOUNTER = 0x4B,    ///< 16-bit step counter
    TAP_CFG = 0x58        ///< Tap/pedometer configuration
};

typedef struct GyroData {
    int16_t rawX;
    int16_t rawy;
    int16_t rawz;

    float x;
    float y;
    float z;
} GyroData;

typedef struct AccelData {
    int16_t rawx;
    int16_t rawy;
    int16_t rawz;

    float x;
    float y;
    float z;
} AccelData;

/*!
 * @brief Class to control and communicate with the LSM6DSOX IMU over I2C
 */
class LSM6DSOX : public I2CDevice {

    public:

    /**
     * @brief Construct a new LSM6DSOX object
     */
    LSM6DSOX(const int slaveAddr);

    ///////////////////
    // LSM6DSOX Data //
    ///////////////////

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

    ////////////////////
    // LSM6DSOX Setup //
    ////////////////////

    // Verify the I2C Address is a LSMDSOX device
    // Returns 0 if verified, else returns the buffer value read from device
    uint16_t verifyI2CAddr();

    // Functions to set different device parameters. Return 0 if successful
    int setupDeviceParams();
    int setupAccel();
    int setupGyro();

    // Software reset the LSM6DSOX device
    // Return 0 if successful
    int swReset();

    // Converts the raw accel data to g
    void convertAccelData(AccelData *accelData);

};

#endif
