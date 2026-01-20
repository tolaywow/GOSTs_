#pragma once
/**
 * @file Grass_hopper.h
 * @author Anatoliy Andreev (tolaywow@gmail.com)
 * @brief Реализация алгоритма блочного шифрования "Кузнечик" из ГОСТ 34.12.2015
 * @version 1.0
 * @date 2026-01-19
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <stdint.h>
/**
 * @brief Класс шифрования блоков по ГОСТ 34.12.2015, Алгоритм "Кузнечик"
 * Создаем класс, погружаем выбранный ключ, при необходимости вызываем методы
 * Give_OT для расшифрования блока и Give_ST для зашифрования блока
 * 
 */
class Grass_hopper
{
  friend class GH_test;

public:
  Grass_hopper();
  virtual ~Grass_hopper();

  virtual void push_key(const uint8_t *key_new);
  virtual void Give_ST(uint8_t *block);
  virtual void Give_OT(uint8_t *block);

protected:
  virtual void xors(const uint8_t *Key, uint8_t *block);
  virtual void S_p(uint8_t *block);
  virtual void S_l(uint8_t *block);
  virtual uint8_t l(const uint8_t *block);
  virtual void L_p(uint8_t *block);
  virtual void L_l(uint8_t *block);
  virtual void key_new(uint8_t *key1, uint8_t *key2, const uint8_t numkey);
  virtual void Form_Key();

private:
  uint8_t key[0x20], keys[0xa][0x10];
  Grass_hopper(const Grass_hopper &);
  Grass_hopper &operator=(const Grass_hopper &);
};
