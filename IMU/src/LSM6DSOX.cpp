
#include "../include/LSM6DSOX.h";

#include <cstdlib>
#include <iostream>

LSM6DSOX::LSM6DSOX(const int dp, const int cp) {
    dataPin = dp;
    clockPin = cp;
    return;
}

int LSM6DSOX::readGyro(GyroData *gyroData) {
    gyroData->x = NaN;
    gyroData->y = NaN;
    gyroData->z = NaN;

    return 0;
}

int LSM6DSOX::readAccelerometer(AccelData *accelData) {

    return 0;
}