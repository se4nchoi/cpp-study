#include <iostream>
#include <cstdint>
#include <bitset>
#include <iomanip> // For printing in Hex

int main() {
  // 1. THE SETUP
  // Imagine this variable is a physical hardware register at address 0x40021000
  // We use 'volatile' because in real life, hardware changes outside our control.
  volatile uint32_t fake_hardware_register = 0;

  std::cout << "Initial Value: " << std::bitset<32>(fake_hardware_register) << std::endl;
  
  // 2. THE POINTER
  // We create a pointer that holds the ADDRESS of our register.
  // In real embedded code, this would look like: 
  // volatile uint32_t* gpio_ptr = (uint32_t*)0x40021000;
  volatile uint32_t* gpio_ptr = &fake_hardware_register;

  std::cout << "Address of Register: 0x" << std::hex << reinterpret_cast<uintptr_t>(gpio_ptr) << std::endl;

  // 3. WRITING (Dereferencing)
  // We want to turn on bit 5 (imagine that's an LED).
  // We use the pointer to go to that address and write data.
  // *gpio_ptr means "Go to the address held in gpio_ptr and access the value"
  
  std::cout << "Pointer address before write: 0x" << std::hex << reinterpret_cast<uintptr_t>(gpio_ptr) << std::endl;
  *gpio_ptr = *gpio_ptr | (1 << 5); // Read, Modify, Write
  std::cout << "Pointer address after write:  0x" << std::hex << reinterpret_cast<uintptr_t>(gpio_ptr) << " (It's the same!)" << std::endl;
  
  std::cout << "Value after setting Bit 5 via pointer: " << std::bitset<32>(*gpio_ptr) << std::endl;

  // 4. POINTER ARITHMETIC (The Interview Trap)
  // If we move the pointer forward by 1, how many bytes does it move?
  std::cout << "\n--- Pointer Arithmetic ---" << std::endl;
  std::cout << "Current Pointer Address: 0x" << std::hex << reinterpret_cast<uintptr_t>(gpio_ptr) << std::endl;
  
  // Increment the pointer
  gpio_ptr++; 
  
  std::cout << "New Pointer Address:     0x" << std::hex << reinterpret_cast<uintptr_t>(gpio_ptr) << std::endl;
  std::cout << "(Notice it increased by 4 bytes, because it points to a uint32_t!)" << std::endl;

  return 0;
}