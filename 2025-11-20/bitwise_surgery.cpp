#include <iostream>
#include <cstdint>
#include <bitset>

// Using defines or consts for bit positions is a common and good practice.
constexpr uint8_t ENGINE_BIT = 0;
constexpr uint8_t LIGHTS_BIT = 1;
constexpr uint8_t WIPERS_BIT = 2;

int main() {
  // Imagine this variable represents a hardware register
  // Bit ENGINE_BIT: Engine On/Off
  // Bit LIGHTS_BIT: Lights On/Off
  // Bit WIPERS_BIT: Wipers On/Off
  uint8_t car_control = 0; // Start with everything off (0000 0000)

  // 1. Turn on the Engine (Set Bit 0)
  // 0000 0000 OR 0000 0001 = 0000 0001
  car_control = car_control | (1 << ENGINE_BIT); 
  std::cout << "1) Control Register: " <<std::bitset<8>(car_control) << std::endl;

  // 2. Turn on the Wipers (Set Bit 2)
  // 0000 0001 OR 0000 0100 = 0000 0101
  car_control = car_control | (1 << WIPERS_BIT);
  std::cout << "2) Control Register: " <<std::bitset<8>(car_control) << std::endl;

  // 3. Turn OFF the Engine (Clear Bit 0) but leave Wipers on
  // We use AND with the Inverse
  // ~(1 << ENGINE_BIT) creates 1111 1110
  // 0000 0101 AND 1111 1110 = 0000 0100
  car_control = car_control & ~(1 << ENGINE_BIT);
  std::cout << "3) Control Register: " <<std::bitset<8>(car_control) << std::endl;

  // 4. Check if Lights are on (Check Bit 1)
  std::cout << "4) Checking lights..." << std::endl;
  if (car_control & (1 << LIGHTS_BIT)) {
      std::cout << "   Lights are ON" << std::endl;
  } else {
      std::cout << "   Lights are OFF" << std::endl;
  }

  return 0;
}