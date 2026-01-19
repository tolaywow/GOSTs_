#pragma once
#include <cstdint>
#include "Facade.h"
#include <vector>

class Psp
{
public:
  Psp(std::vector<uint8_t> key, size_t length_of_hash = 0x200);
  ~Psp();
  void generate(uint8_t *result);

protected:
  uint8_t *h;
  uint8_t *Key;
  size_t length_of_ha;
  Facade Faca;
  void add_key();
};
