#pragma once
/**
 * @file Gamming_with_cloased_loop_by_cipher_text.h
 * @author Anatoliy Andreev (tolaywow@gmail.com)
 * @brief Реализация алгоритма работы блочного шифрования "Кузнечик" в режиме
 * гаммирования с обратной связью по шифртексту из ГОСТ 34.13.2015
 * @version 1.1
 * @date 2026-02-20
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "Grass_hopper.h"
#include <vector>
/**
 * @brief для использования при написании класса создан сокращенный макрос
 *
 */
#define GwCLbCt Gamming_with_cloased_loop_by_cipher_text

/**
 * @brief Есть шаблон, этот класс не использовать. Использовать GWCLbCT
 *
 */
class GwCLbCt : public Grass_hopper
{
  friend class Test_GwCLbCt;

public:
  GwCLbCt(const unsigned short length_of_IV = 0x20);
  virtual ~GwCLbCt();

  virtual void push_IV(const uint8_t *IV);
  virtual void push_IV_and_key(const uint8_t *IV, const uint8_t *key_new);
  virtual void Give_ST(uint8_t *block);
  virtual void Give_OT(uint8_t *block);
  virtual void Give_ST(uint8_t *block, const uint8_t length_last_not_full_block);
  virtual void Give_OT(uint8_t *block, const uint8_t length_last_not_full_block);
  virtual void push_s(const unsigned short s_in = 0x80);

private:
  std::vector<uint8_t> block_R;
  unsigned short s, l_o_IV;
};
