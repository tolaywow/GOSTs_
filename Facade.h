#pragma once
#include <cstdint>
#include "Ihash.h"

class Facade
{
public:
  Facade(size_t length_of_hash = 0x200);
  ~Facade();
  void give_hash(uint8_t *block, uint8_t *result);

protected:
  Ihash *Hash;
  std::vector<uint8_t> block_h;
  uint8_t length_of_hash_8;
};
