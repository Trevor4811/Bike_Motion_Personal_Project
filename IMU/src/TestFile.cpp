#include <iostream>
#include <bitset>


int main(int argc, char **argv) {
    uint8_t totalNumBits = 8;
    uint8_t numBits = 3;
    uint8_t val = 0b010;
    uint8_t offset = 2;
   
    if (offset > totalNumBits-1 || offset < 0) {
        return -1;
    }
    // check write overflow
    if (numBits > offset + 1) {
        return -1;
    }

    uint8_t buf = ~0;

    // Mask bits being written to
    uint8_t ones = ~0;
    uint8_t mask = ones >> (totalNumBits-numBits);
    mask = mask << (offset-numBits+1); // 00110000
    mask = ~mask; // 11001111
    buf = buf & mask;

    // write bits to offset location
    buf = buf | (val << (offset-numBits+1));

    std::cout << "Mask=\t\t" << std::bitset<8>(mask) << "\nbufWrite=\t" << std::bitset<8>(buf) << "\n";
}

