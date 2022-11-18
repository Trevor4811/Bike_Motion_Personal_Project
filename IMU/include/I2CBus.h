#ifndef _I2CBUS_H
#define _I2CBUS_H

#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

typedef char BusString_t[20];

/*!
 * @brief Class that represents communication with a general i2c slave device
 */
class I2CBus {

    public:
    I2CBus();

    BusString_t availableBusses[2];
    
    int *openI2CBus();

    private:

    void getAvailableBusses();

};


#endif
