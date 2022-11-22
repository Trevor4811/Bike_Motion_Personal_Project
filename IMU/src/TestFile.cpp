#include <iostream>
#include <bitset>


int main(int argc, char **argv) {
    uint8_t totalNumBits = 16;
    uint8_t numBits = 1;
    uint16_t val = 0b1;
    uint8_t offset = 7;
    
    uint16_t buf = ~0;

    // Mask bits being written to
    uint16_t ones = ~0;
    uint16_t mask = ones >> (totalNumBits-numBits);
	    //std::pow(2, numBits); // 00000011
    mask = mask << ((totalNumBits-numBits)-offset); // 00001100
    mask = ~mask; // 11110011
    buf = buf & mask;

    // write bits to offset location
    buf = buf | (val << ((totalNumBits-numBits)-offset));

    std::cout << "Mask=\t\t" << std::bitset<16>(mask) << "\nbufWrite=\t" << std::bitset<16>(buf) << "\n";
}

