#include <iostream>
#include <cstdint>
#include <bitset>

enum class PinNum : uint8_t {
  P0 = 0, P2, P3, P4, P5, P6, P7, P8, P9
};

typedef struct {
  volatile uint32_t MODER;
  volatile uint32_t ODR; 
  volatile uint32_t IDR; // input data register
} GPIO_TypeDef;

class Pin {
  private:
    GPIO_TypeDef* port;
    PinNum pin;

  public:
    Pin(GPIO_TypeDef* portAddr, PinNum p) : port(portAddr), pin(p) {}

    void set() {
      uint8_t shift = static_cast<uint8_t>(pin);
      port->ODR |= (1 << shift);
    }

    void clear() {
      uint8_t shift = static_cast<uint8_t>(pin);
      port->ODR &= ~(1 << shift);
    }

    bool read() const{
      uint8_t shift = static_cast<uint8_t>(pin);
      // checking if IDR bit is high (1) or low (0)
      return (port->IDR & (1 << shift));
    }
};


// modern usage
// old C: void check_status(Pin* p)
// => this must check if p is null ptr; and, ugly access p->read()
// modern style: pass by reference (Pin& p)

void monitor_pin(const Pin& p) {
  // we pass a const reference to skip a null check
  // also means
  // 1. we look at the original object, not a copy
  // 2. we promist NOT to modify it; only able to call const methods

  // trying to use a non-const method here would cause a compile error
  // p.set();
  if (p.read()) {
    std::cout << "[MONITOR] Pin is HIGH" << std::endl;
  } else {
    std::cout << "[MONITOR] Pin is LOW" << std::endl;
  }
}

int main() {
  uint32_t fake_mem[3] = {0}; // zero MODER, ODR, IDR
  GPIO_TypeDef* GPIOA = (GPIO_TypeDef*)fake_mem;

  Pin button(GPIOA, PinNum::P5);

  // test 1: simulate button press (hardware should turn bit 5 high)
  button.set();
  std::cout << "ODR Register: " << std::bitset<32>(fake_mem[2]) << std::endl;

  monitor_pin(button);

  // test 2: simulate release
  button.clear();
  std::cout << "ODR Register: " << std::bitset<32>(fake_mem[2]) << std::endl;

  monitor_pin(button);

  return 0;
}