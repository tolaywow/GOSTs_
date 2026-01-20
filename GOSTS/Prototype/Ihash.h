#pragma once
/**
 * @file Ihash.h
 * @author Anatoliy Andreev (tolaywow@gmail.com)
 * @brief Интерфейс для исользования в функциях хэширования
 * @version 1.0
 * @date 2026-01-19
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <cstdint>
#include <vector>

/**
 * @brief Интерфейс класса формирования HASH
 * 
 */
class Ihash
{
public:
  virtual ~Ihash() {} /*= 0*/;
  virtual std::vector<uint8_t> give_hash(uint8_t *text, uint64_t length) = 0;
};
