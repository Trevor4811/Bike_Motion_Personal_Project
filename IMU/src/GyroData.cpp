
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/GyroData.h";
#include "StringUtils.cpp";


GyroData::GyroData(int8_t gyroDataRange) {
    this->gyroDataRange = gyroDataRange;
}

int GyroData::csvFormat(char* data) {
    int bufLen = sizeof(data);
    if (bufLen < 140) {
        return -1;
    }

    data[0] = '\0';
    csvFormatRaw(data);
    csvFormatAdj(data);
    // char* endRaw = stpncpy(data, csvFormatRaw(), bufLen/2);
    // strncat(data,, bufLen/2);
    return 0;
}
int GyroData::csvFormatRaw(char* data) {
    int numCharsPerVal = 16;
    
    if (spaceLeftInString(data) < (numCharsPerVal*3+1)+1) { 
        return -1;
    }
    
    char temp[33];
    itoa(rawx, temp, 10);
    strncat(data, temp, numCharsPerVal);
    strncat(data, ",", numCharsPerVal);
    itoa(rawy, temp, 10);
    strncat(data, temp, numCharsPerVal);
    strncat(data, ",", numCharsPerVal);
    itoa(rawz, temp, 10);
    strncat(data, temp, numCharsPerVal);
    strncat(data, ",", numCharsPerVal);
    
    return 0;
}
int GyroData::csvFormatAdj(char* data) {
    int numCharsPerVal = 16;
    
    if (spaceLeftInString(data) < (numCharsPerVal*3+1)+1) { 
        return -1;
    }

    char temp[33];
    itoa(x, temp, 10);
    strncat(data, temp, numCharsPerVal);
    strncat(data, ",", numCharsPerVal);
    itoa(y, temp, 10);
    strncat(data, temp, numCharsPerVal);
    strncat(data, ",", numCharsPerVal);
    itoa(z, temp, 10);
    strncat(data, temp, numCharsPerVal);
    strncat(data, ",", numCharsPerVal);

    return 0;
}

int GyroData::convertRawData() {
    x = rawx;
    y = rawy;
    z = rawz;

    return 0;
}
