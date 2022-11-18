#include <string>
#include <iostream>
#include <filesystem>

#include "../include/I2CBus.h"

namespace fs = std::filesystem;

I2CBus::I2CBus() {
    getAvailableBusses();
}

int *I2CBus::openI2CBus() {
    int *file = new int;
    char filename[40];
    int device_num = 1;

    std::snprintf(filename, 19, "/dev/i2c-%d", device_num);
    *file = std::open(filename, O_RDWR);
    if (*file < 0) {
        return -1;
    }
    return file;
}


// i2c-1
void I2CBus::getAvailableBusses() {
    return;
    std::string path = "/sys/class/i2c-dev/";

    for (const auto & entry : fs::directory_iterator(path))
        char tempVal[20];
        std::strncpy(tempVal, entry.path(), 19)
        char **possibleStrings = {"i2c-1", "i2c-2"};
        bool valid = true;
        for (int i = 0, i < 6; i++) {
            
        }
        std::cout << entry.path() << std::endl;

}

// Test bus open
int main(int argc, char** argv) {
    I2CBus::I2CBus bus = I2CBus::I2CBus();
    int filenum = bus.openI2CBus();
    std::cout << filenum << std::endl;
    
}

#endif