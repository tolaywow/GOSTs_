#pragma once
/**
 * @file GwCLbCT.h
 * @author Anatoliy Andreev (tolaywow@gmail.com)
 * @brief Реализация шаблона алгоритма работы блочного шифрования в режиме
 * гаммирования с обратной связью по шифртексту из ГОСТ 34.13.2015
 * @version 1.2
 * @date 2026-02-20
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <cstdint>
#include <stdexcept>
#include <vector>

template <class CRYPTO, const size_t n>
class GwCLbCT : protected CRYPTO
{
public:
  GwCLbCT(const uint16_t length_of_IV = n / 0x8);
  virtual ~GwCLbCT();

  virtual void push_IV(const uint8_t *IV);
  virtual void push_IV_and_key(const uint8_t *IV, const uint8_t *key_new);
  // virtual void Give_ST(uint8_t* block);
  // virtual void Give_OT(uint8_t* block);
  virtual void Give_ST(uint8_t *block, uint16_t length_last_not_full_block = n / 0x8);
  virtual void Give_OT(uint8_t *block, uint16_t length_last_not_full_block = n / 0x8);
  virtual void push_s(const uint16_t s_in = n / 0x8);

private:
  std::vector<uint8_t> R;
  uint16_t s, l_o_IV;
};

template <class CRYPTO, size_t n>
inline GwCLbCT<CRYPTO, n>::GwCLbCT(const uint16_t length_of_IV) : l_o_IV(length_of_IV), s(n / 0x8)
{
  if (length_of_IV < 0x1)
  {
    throw std::invalid_argument(length_of_IV);
  }

  R.resize(length_of_IV);
}

template <class CRYPTO, size_t n>
inline GwCLbCT<CRYPTO, n>::~GwCLbCT()
{
}

template <class CRYPTO, size_t n>
inline void GwCLbCT<CRYPTO, n>::push_IV(const uint8_t *IV)
{
  if (IV == nullptr)
  {
    throw std::invalid_argument("IV");
  }

  for (uint8_t i = 0; i < l_o_IV; i++)
  {
    R[i] = IV[i];
  }
}

template <class CRYPTO, size_t n>
inline void GwCLbCT<CRYPTO, n>::push_IV_and_key(const uint8_t *IV, const uint8_t *key_new)
{
  push_IV(IV);
  CRYPTO::push_key(key_new);
}

template <class CRYPTO, size_t n>
inline void GwCLbCT<CRYPTO, n>::Give_ST(uint8_t *block, uint16_t length_last_not_full_block)
{
  if (block == nullptr)
  {
    throw std::invalid_argument("block");
  }
  uint8_t block_var[n / 0x8] = {0};

  for (uint8_t i = 0; i < n / 0x8; i++)
  {
    block_var[i] = R[l_o_IV - n / 0x8 + i];
  }

  CRYPTO::Give_ST(block_var);

  for (uint8_t i = 0; i < l_o_IV - s; i++)
  {
    R[l_o_IV - 0x1 - i] = R[l_o_IV - i - 0x1 - s];
  }

  {
    uint16_t temp;
    if (length_last_not_full_block > s)
    {
      temp = s;
    }
    else
    {
      temp = length_last_not_full_block;
    }

    for (uint8_t i = 0; i < temp; i++)
    {
      block[i] ^= block_var[i + n / 0x8 - temp];
      R[i] = block[i];
    }
  }
}

template <class CRYPTO, size_t n>
inline void GwCLbCT<CRYPTO, n>::Give_OT(uint8_t *block, uint16_t length_last_not_full_block)
{
  if (block == nullptr)
  {
    throw std::invalid_argument("block");
  }
  if (length_last_not_full_block < 1)
  {
    throw std::invalid_argument("length_last_not_full_block");
  }

  uint8_t block_var[n / 0x8] = {0};

  for (uint8_t i = 0; i < n / 0x8; i++)
  {
    block_var[i] = R[l_o_IV - n / 0x8 + i];
  }

  CRYPTO::Give_ST(block_var);

  for (uint8_t i = 0; i < l_o_IV - s; i++)
  {
    R[l_o_IV - 0x1 - i] = R[l_o_IV - i - 0x1 - s];
  }

  {
    uint16_t temp;
    if (length_last_not_full_block >= s)
    {
      temp = s;
    }
    else
    {
      temp = length_last_not_full_block;
    }
    for (uint8_t i = 0; i < temp; i++)
    {
      R[i] = block[i];
      block[i] ^= block_var[i + n / 0x8 - temp];
    }
  }
}

template <class CRYPTO, size_t n>
inline void GwCLbCT<CRYPTO, n>::push_s(const uint16_t s_in)
{
  s = s_in;
}
