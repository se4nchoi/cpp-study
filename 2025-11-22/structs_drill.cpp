#include <iostream>
#include <cstdint>
#include <bitset>

// 1. DEFINE THE HARDWARE MAP
// In STM32, 'volatile' is put on the member variables inside the struct
// because these specific memory slots can change via hardware.
typedef struct {
    volatile uint32_t MODER;  // Offset: 0x00 (Sets Pin Mode: Input/Output)
    volatile uint32_t OTYPER; // Offset: 0x04 (Output Type: Push-Pull/Open-Drain)
    volatile uint32_t OSPEEDR;// Offset: 0x08 (Speed)
    volatile uint32_t PUPDR;  // Offset: 0x0C (Pull-up/Pull-down)
    volatile uint32_t IDR;    // Offset: 0x10 (Input Data - Read Only)
    volatile uint32_t ODR;    // Offset: 0x14 (Output Data - Write 1 to turn LED on)
} GPIO_TypeDef;

int main() {
    // 2. SIMULATE HARDWARE MEMORY
    // In real life, this address is fixed (e.g., 0x40020000).
    // On PC, we allocate an array of 6 uint32_ts to act as our "hardware".
    uint32_t fake_hardware_memory[6] = {0}; 

    // 3. CREATE THE PERIPHERAL POINTER
    // We cast the address of our array to a pointer of our Struct type.
    // Now 'GPIOA' thinks it is looking at a hardware block.
    GPIO_TypeDef* GPIOA = (GPIO_TypeDef*)fake_hardware_memory;

    std::cout << "--- Initial State ---" << std::endl;
    std::cout << "Address of Memory: " << fake_hardware_memory << std::endl;
    std::cout << "Address of GPIOA:  " << GPIOA << std::endl; // Should be same

    // 4. THE DRIVER LOGIC (This is what you will write for STM32)
    // Goal: Configure Pin 5 as Output and Turn it ON.
    
    // Step A: Set Pin 5 to Output Mode in MODER register.
    // (Assume '01' binary pattern means Output for a pin)
    // Pin 5 uses bits 10 and 11 (2 bits per pin).
    // We want to write '01' into bits [11:10].
    GPIOA->MODER |= (1 << 10); // Set bit 10
    GPIOA->MODER &= ~(1 << 11); // Clear bit 11
    
    // Step B: Turn Pin 5 ON in ODR register.
    // ODR has 1 bit per pin. Bit 5 controls Pin 5.
    GPIOA->ODR |= (1 << 5);

    // 5. VERIFY
    // Did our struct pointer actually modify the raw memory array?
    std::cout << "\n--- Verification ---" << std::endl;
    std::cout << "MODER Register: " << std::bitset<32>(GPIOA->MODER) << std::endl;
    std::cout << "ODR Register:   " << std::bitset<32>(GPIOA->ODR) << std::endl;
    
    // Check the raw array index 0 (MODER) and index 5 (ODR)
    if (fake_hardware_memory[5] == (1 << 5)) {
        std::cout << "SUCCESS: The raw memory was updated correctly via the struct!" << std::endl;
    } else {
        std::cout << "FAILURE: Memory check failed." << std::endl;
    }

    return 0;
}