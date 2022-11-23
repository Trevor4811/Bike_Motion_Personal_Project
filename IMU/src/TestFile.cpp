#include <iostream>
#include <bitset>


int main(int argc, char **argv) {
    uint8_t totalNumBits = 8;
    uint8_t numBits = 5;
    uint8_t val = 0b010;
    uint8_t offset = 4;
   
    if (offset > totalNumBits-1 || offset < 0) {
        return -1;
    }
    // check write overflow
    if (numBits > offset + 1) {
        return -1;
    }

    uint8_t buf = 0b11101011;

    // Shift bits to LSB
    buf = buf >> (offset-numBits+1);
    // Mask bits not being read
    uint8_t ones = ~0;
    uint8_t mask = ones >> (totalNumBits-numBits);
    buf = buf & mask;

    std::cout << "Mask=\t\t" << std::bitset<8>(mask) << "\nbufWrite=\t" << std::bitset<8>(buf) << "\n";
}

