#include <cstdint>

// 1. DEFINE THE ADDRESSES (The "Map")
// We cast the raw hex numbers to pointers so we can use them.
// 'volatile' is crucial because hardware changes these values, not just code.

// RCC (Clock Control) Base + Offset
#define RCC_BASE        0x40023800UL
#define RCC_AHB1ENR     (*((volatile uint32_t *)(RCC_BASE + 0x30)))

// GPIOA Base Address
#define GPIOA_BASE      0x40020000UL
#define GPIOA_MODER     (*((volatile uint32_t *)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR       (*((volatile uint32_t *)(GPIOA_BASE + 0x14)))

// 2. MAIN LOGIC
// This function would be the entry point on your microcontroller
void main_app() {
    // --- STEP 1: Enable the Clock ---
    // The LED is on Port A. We must enable GPIOA in the RCC register.
    // Bit 0 controls GPIOA.
    // Set Bit 0 to 1.
    RCC_AHB1ENR |= (1 << 0);

    // --- STEP 2: Configure Pin 5 as Output ---
    // In MODER, every pin has 2 bits. Pin 5 uses Bits [11:10].
    // 00 = Input, 01 = Output, 10 = Alternate, 11 = Analog
    // We want '01' (Output).
    
    // First, clear both bits (Safety step)
    GPIOA_MODER &= ~(3 << 10); // Clear bits 10 and 11 (3 is 11 in binary)
    
    // Now, set Bit 10 to 1
    GPIOA_MODER |= (1 << 10);  // Set bit 10 to 1. Result: 01

    // --- STEP 3: Blink Loop ---
    while (1) {
        // Turn LED ON (Set Pin 5 HIGH)
        GPIOA_ODR |= (1 << 5);

        // Fake Delay (Bad practice, but works for simple test)
        for (volatile int i = 0; i < 100000; i++);

        // Turn LED OFF (Set Pin 5 LOW)
        GPIOA_ODR &= ~(1 << 5);

        // Fake Delay
        for (volatile int i = 0; i < 100000; i++);
    }
}

// Note: On a PC, you can't run this main_app()! 
// It tries to write to 0x40023800, which is restricted OS memory.
// But on the STM32, this is exactly how you blink the LED.
int main() {
    // If you run this on PC, it segfaults.
    // main_app(); 
    return 0;
}