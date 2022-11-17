#ifndef _I2SSENSOR_H
#define _I2SSENSOR_H

/*!
 * @brief Class that represents a general i2s sensor
 */
class i2sSensor {

    protected:

    int dataPin;
    int clockPin;
    
    int writeBuffer();
    int readBuffer();

    public:

};


#endif