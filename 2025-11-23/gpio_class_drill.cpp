#include <iostream>
#include <cstdint>
#include <bitset>

// 1. THE HARDWARE MAP (Same as yesterday)
typedef struct {
    volatile uint32_t MODER;  // 0x00
    volatile uint32_t OTYPER; // 0x04
    volatile uint32_t OSPEEDR;// 0x08
    volatile uint32_t PUPDR;  // 0x0C
    volatile uint32_t IDR;    // 0x10
    volatile uint32_t ODR;    // 0x14
} GPIO_TypeDef;

// 2. THE DRIVER CLASS
// This class "wraps" the raw hardware so the main code is clean.
class Pin {
private:
    GPIO_TypeDef* port; // Which Port? (GPIOA, GPIOB...)
    uint8_t pinNumber;  // Which Pin? (0-15)

public:
    // Constructor: "Injects" the hardware dependency
    Pin(GPIO_TypeDef* portAddress, uint8_t pin) 
        : port(portAddress), pinNumber(pin) {}

    // Configure the pin as Output
    void modeOutput() {
        // 1. Clear the 2 bits for this pin (Safety)
        // Each pin takes 2 bits in MODER. So Pin 5 starts at bit 10.
        uint8_t shift = pinNumber * 2;
        port->MODER &= ~(3 << shift); 

        // 2. Set the '01' pattern for Output
        port->MODER |= (1 << shift);
    }

    // Turn Pin ON (High)
    void set() {
        port->ODR |= (1 << pinNumber);
    }

    // Turn Pin OFF (Low)
    void clear() {
        port->ODR &= ~(1 << pinNumber);
    }
    
    // Toggle (Flip state) - A bonus C++ feature!
    void toggle() {
        port->ODR ^= (1 << pinNumber);
    }
};

int main() {
    // 3. SIMULATE THE HARDWARE (The Test Bench)
    // In real life, this array doesn't exist; it's real silicon.
    uint32_t fake_gpio_a[6] = {0}; 
    GPIO_TypeDef* GPIOA = (GPIO_TypeDef*)fake_gpio_a;

    std::cout << "--- Testing the Pin Class ---" << std::endl;

    // 4. INSTANTIATE THE OBJECT
    // "I want a Pin object representing Pin 5 on Port A"
    Pin myLed(GPIOA, 5);

    // 5. USE THE DRIVER (Look how clean this main code is!)
    myLed.modeOutput();
    myLed.set();

    // 6. VERIFY (Did it touch the "hardware" correctly?)
    // We check the raw ODR register. It should have bit 5 set.
    if (GPIOA->ODR == (1 << 5)) {
        std::cout << "[SUCCESS] LED turned ON. ODR Register: " 
                  << std::bitset<32>(GPIOA->ODR) << std::endl;
    } else {
        std::cout << "[FAIL] ODR Register: " 
                  << std::bitset<32>(GPIOA->ODR) << std::endl;
    }

    // Test Toggle
    myLed.toggle();
    std::cout << "After Toggle (Should be 0): " << std::bitset<32>(GPIOA->ODR) << std::endl;

    return 0;
}