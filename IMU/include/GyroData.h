#ifndef GYRODATA_H
#define GYRODATA_H

#include <stdint.h>

#include "IMUData.h";

class GyroData : public IMUData {
    public:
    virtual int csvFormat(char* data);
    virtual int csvFormatRaw(char* data);
    virtual int csvFormatAdj(char* data);

    virtual int convertRawData();

    GyroData(int8_t gyroDataRange);

    uint16_t rawx;
    uint16_t rawy;
    uint16_t rawz;

    float x;
    float y;
    float z;

    private:

    int8_t gyroDataRange;

};

#endif