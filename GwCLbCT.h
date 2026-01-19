#pragma once
#include <cstdint>

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
  uint8_t *R;
  uint16_t s, l_o_IV;
};

template <class CRYPTO, size_t n>
inline GwCLbCT<CRYPTO, n>::GwCLbCT(const uint16_t length_of_IV) : l_o_IV(length_of_IV), s(n / 0x8)
{
  R = new uint8_t[l_o_IV];
}

template <class CRYPTO, size_t n>
inline GwCLbCT<CRYPTO, n>::~GwCLbCT()
{
  delete[] R;
}

template <class CRYPTO, size_t n>
inline void GwCLbCT<CRYPTO, n>::push_IV(const uint8_t *IV)
{
  for (uint8_t i = 0; i < l_o_IV; i++)
    R[i] = IV[i];
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
  uint8_t block_var[n / 0x8] = {0};

  for (uint8_t i = 0; i < n / 0x8; i++)
    block_var[i] = R[l_o_IV - n / 0x8 + i];

  CRYPTO::Give_ST(block_var);

  for (uint8_t i = 0; i < l_o_IV - s; i++)
    R[l_o_IV - 0x1 - i] = R[l_o_IV - i - 0x1 - s];

  {
    uint16_t temp;
    if (length_last_not_full_block > s)
      temp = s;
    else
      temp = length_last_not_full_block;

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
  uint8_t block_var[n / 0x8] = {0};

  for (uint8_t i = 0; i < n / 0x8; i++)
    block_var[i] = R[l_o_IV - n / 0x8 + i];

  CRYPTO::Give_ST(block_var);

  for (uint8_t i = 0; i < l_o_IV - s; i++)
    R[l_o_IV - 0x1 - i] = R[l_o_IV - i - 0x1 - s];

  {
    uint16_t temp;
    if (length_last_not_full_block >= s)
      temp = s;
    else
      temp = length_last_not_full_block;

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
