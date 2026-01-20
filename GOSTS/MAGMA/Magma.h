#pragma once
/**
 * @file Magma.h
 * @author Anatoliy Andreev (tolaywow@gmail.com)
 * @brief Реализация алгоритма блочного шифрования "Магма" из ГОСТ 34.12.2015
 * @version 1.0
 * @date 2026-01-19
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <cstdint>
class Magma
{
public:
  Magma();
  virtual ~Magma() {};

  virtual void push_key(const uint8_t *key_new);
  virtual void Give_ST(uint8_t *block);
  virtual void Give_OT(uint8_t *block);

protected:
  virtual void g_k(uint8_t *text, const uint8_t *key);
  virtual void G_k(uint8_t *a0, uint8_t *a1, const uint8_t num_of_key);
  virtual void Gs_k(uint8_t *a0, uint8_t *a1);

private:
  uint8_t K[0x20]; // Ki=K[0x4*(i-0x1)]
  Magma(const Magma &);
  Magma &operator=(const Magma &);
};
