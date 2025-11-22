#include <iostream>
#include <cstdint>
#include <bitset>

// one 8-bit register for a smart thermostat

// Using defines or consts for bit positions is a common and good practice.
constexpr uint8_t HEATING_BIT = 0;
constexpr uint8_t COOLING_BIT = 1;
constexpr uint8_t FAN_BIT = 2;
constexpr uint8_t SAFETY_LOCK_BIT = 3;

int main() {
  // Requirements:
  // 1. start with system_status = 0
  // 2. Function (1): write code to turn heating and Fan ON in a single line.
  // 3. Function (2): write code to toggle safety lock
  // 4. Function (3): write code for a safety check -- 
  // if heat and cooling are both ON at same time, force system to 0

  std::cout << "Simulating Air Conditioner Scenarios" << std::endl;
  std::cout << "(1) Turn Heating and Fan ON" << std::endl;
  std::cout << "(2) Toggle Safety Lock" << std::endl;
  std::cout << "(3) Safety Check for Heating and Cooling Conflict" << std::endl;
  std::cout << "-----------------------------------------------------" << std::endl;

  uint8_t system_status = 0; // All systems off (0000 0000)

  system_status = system_status | (1 << HEATING_BIT) | (1 << FAN_BIT);
  std::cout << "1) Control Register: " <<std::bitset<8>(system_status) << std::endl;

  system_status = system_status ^ (1 << SAFETY_LOCK_BIT);
  std::cout << "2) Control Register: " <<std::bitset<8>(system_status) << std::endl;

  // TEST: Let's force a bad state (Turn Cooling ON while Heating is already ON)
  system_status |= (1 << COOLING_BIT);
  std::cout << "3) Forced Bad State: " << std::bitset<8>(system_status) << std::endl;

  // Safety Override Check
  uint8_t conflict_mask = (1 << HEATING_BIT) | (1 << COOLING_BIT);

  // Check if BOTH bits are set
  if ((system_status & conflict_mask) == conflict_mask) {
      std::cout << "[!] CRITICAL: Heating and Cooling active! Performing Emergency Shutdown." << std::endl;
      system_status = 0x00; // Hard Reset
  } else {
      std::cout << "Operating normally..." << std::endl;
  }

  std::cout << "4) Final Status: " << std::bitset<8>(system_status) << std::endl;

  return 0;
}
