#include <iostream>
#include <cstdint>
#include <cstring>

// 1. THE NAIVE STRUCT (Standard C++)
// The CPU adds 'Padding' to make access faster.
struct NormalFrame {
  uint8_t  id;      // 1 byte
  // ... [3 bytes of invisible padding inserted here by compiler] ...
  uint32_t data;    // 4 bytes
  uint16_t checksum;// 2 bytes
  // ... [2 bytes of padding to align the TOTAL size to 4 bytes] ...
};

// 2. THE PACKED STRUCT (Embedded Standard)
// We tell the compiler: "Do NOT add padding. Crunch it together."
// This is slower for the CPU to read, but REQUIRED for networking/radio.
// Syntax: __attribute__((packed)) is GCC/Clang specific.
struct __attribute__((packed)) PackedFrame {
  uint8_t  id;      // 1 byte
  uint32_t data;    // 4 bytes
  uint16_t checksum;// 2 bytes
};

int main() {
  std::cout << "--- Memory Alignment Drill ---" << std::endl;

  // PREDICTION TIME: 
  // Normal: 1 + 4 + 2 = 7 bytes "logic", but actual size will be 12.
  // Packed: 1 + 4 + 2 = 7 bytes exactly.

  std::cout << "Size of NormalFrame: " << sizeof(NormalFrame) << " bytes" << std::endl;
  std::cout << "Size of PackedFrame: " << sizeof(PackedFrame) << " bytes" << std::endl;

  // THE REAL WORLD SCENARIO: Sending this over CAN Bus
  // We treat the struct as a raw byte array to send it.
  PackedFrame myMsg;
  myMsg.id = 0xA;
  myMsg.data = 0x12345678;
  myMsg.checksum = 0xFFFF;

  // View it as raw memory bytes
  uint8_t* raw_bytes = (uint8_t*)&myMsg;

  std::cout << "\nRaw Bytes to Wire: ";
  for(int i=0; i < sizeof(PackedFrame); i++) {
    // printf is often easier for hex printing than cout
    printf("%02X ", raw_bytes[i]);
  }
  std::cout << std::endl;

  return 0;
}