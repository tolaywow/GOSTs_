#pragma once
/**
 * @file Facade.h
 * @author Anatoliy Andreev (tolaywow@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-01-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
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
