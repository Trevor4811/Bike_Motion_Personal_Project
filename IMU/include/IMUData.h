#ifndef IMUDATA_H
#define IMUDATA_H

class IMUData {
    public:
    
    virtual int csvFormat(char* data) = 0;
    virtual int csvFormatRaw(char* data) = 0;
    virtual int csvFormatAdj(char* data) = 0;

    virtual int convertRawData() = 0;
};

/*


void LSM6DSOX::convertGyroData(GyroData *gyroData) {
    gyroData->x = gyroData->rawx;
    gyroData->y = gyroData->rawy;
    gyroData->z = gyroData->rawz;
}
*/
#endif
