#include <iostream>
#include <cstdint> // <--- The most important header for embedded
#include <bitset>  // Useful for visualizing binary

void print_binary(uint32_t value) {
    // Prints the number in binary format (32 bits)
    std::cout << std::bitset<32>(value) << " : " << value << std::endl;
}

int main() {
    // 1. Fixed Width Integers
    // An STM32 register is usually 32 bits wide.
    uint32_t control_register = 0; 
    
    // A sensor reading might be only 16 bits.
    uint16_t sensor_data = 0xFFFF; 

    // A simple flag or counter might be 8 bits.
    uint8_t counter = 255;

    std::cout << "--- Fixed Width Sizes ---" << std::endl;
    std::cout << "Size of uint8_t:  " << sizeof(uint8_t) << " bytes" << std::endl;
    std::cout << "Size of uint16_t: " << sizeof(uint16_t) << " bytes" << std::endl;
    std::cout << "Size of uint32_t: " << sizeof(uint32_t) << " bytes" << std::endl;

    // 2. Overflow behavior (Critical in embedded)
    // What happens if we add 1 to the max value of an 8-bit integer?
    std::cout << "\n--- Overflow Check ---" << std::endl;
    std::cout << "Counter before: " << (int)counter << std::endl; // Cast to int to print number, not char
    counter = counter + 1;
    std::cout << "Counter after +1: " << (int)counter << " (It rolled over!)" << std::endl;

    return 0;
}