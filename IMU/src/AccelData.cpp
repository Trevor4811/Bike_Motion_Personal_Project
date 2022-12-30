
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/AccelData.h";
#include "StringUtils.cpp";


AccelData::AccelData(int8_t accelDataRange) {
    this->accelDataRange = accelDataRange;
}

int AccelData::csvFormat(char* data) {
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
int AccelData::csvFormatRaw(char* data) {
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
int AccelData::csvFormatAdj(char* data) {
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

int AccelData::convertRawData() {
    x = rawx;
    y = rawy;
    z = rawz;

    return 0;
}
