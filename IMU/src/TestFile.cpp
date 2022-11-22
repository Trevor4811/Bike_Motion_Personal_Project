#include <iostream>
#include <bitset>


int main(int argc, char **argv) {
    uint8_t totalNumBits = 16;
    uint8_t numBits = 1;
    uint16_t val = 0b1;
    uint8_t offset = 7;
    
    uint16_t buf = ~0;

    // Mask bits being written to
    uint8_t ones = ~0;
    uint8_t mask = ones << (totalNumBits-numBits);
    mask = mask >> offset; // 00110000
    mask = ~mask; // 11001111
    buf = buf & mask;

    // write bits to offset location
    buf = buf | (val << ((totalNumBits-numBits)-offset));

    std::cout << "Mask=\t\t" << std::bitset<16>(mask) << "\nbufWrite=\t" << std::bitset<16>(buf) << "\n";
}

