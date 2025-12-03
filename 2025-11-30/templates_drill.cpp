#include <iostream>
#include <cstdint>
#include <bitset>

// 1. Hardware constants
constexpr uint32_t GPIOA_BASE = 0x40020000;
constexpr uint32_t GPIOB_BASE = 0x40020400;

// Struct layout (same as always)
struct GPIO_TypeDef {
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
};

// 2. TEMPLATE DRIVER
// <uint32_t PortAddr>  -> compiler hardcodes this address
// <uint8_t PinNum>     -> compiler hardcodes this bit shift

template <uint32_t PortAddr, uint8_t PinNum>
class Gpio {
  public:
    // static = no need for an instance of Gpio to call this

    static_assert(PinNum < 16, "Error: PinNum must be 0-15");

    static void init() {
      // reinterpret_cast: treat an integer as a pointer
      GPIO_TypeDef* port = reinterpret_cast<GPIO_TypeDef*>(PortAddr);
      
      // this is calculated by compiler at compile time
      port->MODER |= (1 << (PinNum * 2));
    }

    static void set() {
      std::cout << "[HARDWARE OP] Writing to Address: 0x" << std::hex << PortAddr 
                  << " | Bit: " << std::dec << (int)PinNum << std::endl;

        /* REAL EMBEDDED CODE:
        GPIO_TypeDef* port = reinterpret_cast<GPIO_TypeDef*>(PortAddr);
        port->ODR |= (1 << PinNum);
        */
    }

    static void clear() {
      GPIO_TypeDef* port = reinterpret_cast<GPIO_TypeDef*>(PortAddr);
      port->ODR &= ~(1 << PinNum);
    }
};

int main () {
  // type alias
  using LedPin = Gpio<GPIOA_BASE, 5>;
  using PumpPin = Gpio<GPIOB_BASE, 13>;

  std::cout << "--- Template Driver Test ---" << std::endl;
  LedPin::set();
  PumpPin::set();
  
  // THE SAFETY TEST
  // Uncomment the line below. 
  // It won't just crash—it will REFUSE TO COMPILE.
  // using BadPin = Gpio<GPIOA_BASE, 20>;
  // BadPin::set();
  // std::cout << "--- Bad Pin ? ---" << std::endl;


  return 0;
}