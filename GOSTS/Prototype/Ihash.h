#pragma once
#include <cstdint>
#include <vector>

class Ihash
{
public:
  virtual ~Ihash() {} /*= 0*/;
  virtual std::vector<uint8_t> give_hash(uint8_t *text, uint64_t length) = 0;
};
