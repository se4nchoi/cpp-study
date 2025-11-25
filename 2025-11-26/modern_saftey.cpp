#include <iostream>
#include <cstdint>
#include <bitset>


// ENUM Class
enum class PinNum : uint8_t {
  P0= 0, P2, P3, P4, P5, P6, P7, P8, P9,
  P10, P11, P12, P13, P14, P15
};

enum class Port : uint8_t {
  A = 0, B, C
};

// CONSTEXPR
// replaces #DEFINE
constexpr uint32_t FAKE_ADDR_A = 0x40020000;

typedef struct {
  volatile uint32_t MODER;
  volatile uint32_t ODR; 
} GPIO_Typedef;

// Modern Class
class Pin {
  private:
    GPIO_Typedef* port;
    PinNum pin; // this stores the Enum, not a raw int

  public:
    // constructor now requires a PinNum type instead of int
    // i.e. not p = 5, but p = PinNum::P5
    Pin(GPIO_Typedef* portAddr, PinNum p)
      : port(portAddr), pin(p) {}
    
    void set() {
      // need to cast enum to int to do math;
      // annoyance = price of safety
      uint8_t shift = static_cast<uint8_t>(pin);
      port->ODR |= (1 << shift);
    }

    void toggle() {
      uint8_t shift = static_cast<uint8_t>(pin);
      port->ODR ^= (1 << shift);
    }

    void clear() {
      uint8_t shift = static_cast<uint8_t>(pin);
      port->ODR &= ~(1 << shift);
    }
};

int main() {
  uint32_t fake_mem[2] = {0};
  GPIO_Typedef* GPIOA = (GPIO_Typedef*)fake_mem;

  // valid use
  Pin led(GPIOA, PinNum::P5);
  led.set();
  std::cout << "ODR Register: " << std::bitset<32>(fake_mem[1]) << std::endl;
  led.toggle();
  std::cout << "ODR Register: " << std::bitset<32>(fake_mem[1]) << std::endl;
  led.toggle();
  std::cout << "ODR Register: " << std::bitset<32>(fake_mem[1]) << std::endl;
  led.clear();
  std::cout << "ODR Register: " << std::bitset<32>(fake_mem[1]) << std::endl;

  // invalid
  // Pin qled(GPIOA, PinNum::P10);
  
  return 0;
}