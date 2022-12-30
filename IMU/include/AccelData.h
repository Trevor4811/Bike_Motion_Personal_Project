#ifndef ACCELDATA_H
#define ACCELDATA_H

#include <stdint.h>

#include "IMUData.h";

class AccelData : public IMUData {
    public:
    virtual int csvFormat(char* data);
    virtual int csvFormatRaw(char* data);
    virtual int csvFormatAdj(char* data);

    virtual int convertRawData();

    AccelData(int8_t accelDataRange);

    uint16_t rawx;
    uint16_t rawy;
    uint16_t rawz;

    float x;
    float y;
    float z;

    private:

    int8_t accelDataRange;

};

#endif