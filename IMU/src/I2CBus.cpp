#include <string>
#include <iostream>
//#include <fstream>
//#include <i2cFilesystem>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "../include/I2CBus.h"

I2CBus::I2CBus() {
    getAvailableBusses();
}

int I2CBus::openI2CBus() {
    int i2cFile;
    char i2cFilename[40];
    int device_num = 1;

    snprintf(i2cFilename, 19, "/dev/i2c-%d", device_num);
    i2cFile = open(i2cFilename, O_RDWR);
    return i2cFile;
}


// i2c-1
void I2CBus::getAvailableBusses() {
    return;
    /*std::string path = "/sys/class/i2c-dev/";

    for (const auto & entry : fs::directory_iterator(path))
        char tempVal[20];
        std::strncpy(tempVal, entry.path(), 19)
        char **possibleStrings = {"i2c-1", "i2c-2"};
        bool valid = true;
        for (int i = 0, i < 6; i++) {
            
        }
        std::cout << entry.path() << std::endl;
    */
}

/*
// Test bus open
int main(int argc, char** argv) {
    I2CBus bus;
    int *i2cFilenum = bus.openI2CBus();
    std::cout << *i2cFilenum << "\n";
    delete i2cFilenum;
}
*/
