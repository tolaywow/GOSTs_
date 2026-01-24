#pragma once
/**
 * @file Psp.h
 * @author Anatoliy Andreev (tolaywow@gmail.com)
 * @brief Генератор псевдослучайной последовательности на основе STRIBOG
 * @version 1.0
 * @date 2026-01-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <cstdint>
#include "Facade.h"
#include <vector>
/**
 * @brief Класс генератора ПСП
 * 
 */
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
