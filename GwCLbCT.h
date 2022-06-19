#pragma once
#include "abbreviation.h"

template <class CRYPTO, const size_t n>
class GwCLbCT:protected CRYPTO
{
public:
  GwCLbCT(const UI16 length_of_IV =n/0x8);
  virtual ~GwCLbCT();

  virtual void push_IV(const UI8* IV);
  virtual void push_IV_and_key(const UI8* IV, const UI8* key_new);
  //virtual void Give_ST(UI8* block);
  //virtual void Give_OT(UI8* block);
  virtual void Give_ST(UI8* block, UI16 length_last_not_full_block = n / 0x8);
  virtual void Give_OT(UI8* block, UI16 length_last_not_full_block = n / 0x8);
  virtual void push_s(const UI16 s_in = n/0x8);

private:
  UI8* R;
  UI16 s, l_o_IV;
};

template<class CRYPTO, size_t n>
inline GwCLbCT<CRYPTO, n>::GwCLbCT(const UI16 length_of_IV) :
  l_o_IV(length_of_IV), s(n/0x8)
{
  R = new UI8[l_o_IV];
}

template<class CRYPTO, size_t n>
inline GwCLbCT<CRYPTO, n>::~GwCLbCT()
{
  delete[] R;
}

template<class CRYPTO, size_t n>
inline void GwCLbCT<CRYPTO, n>::push_IV(const UI8* IV)
{
  for (UI8 i = 0; i < l_o_IV; i++)
    R[i] = IV[i];
}

template<class CRYPTO, size_t n>
inline void GwCLbCT<CRYPTO, n>::push_IV_and_key(const UI8* IV, const UI8* key_new)
{
  push_IV(IV);
  CRYPTO::push_key(key_new);
}

template<class CRYPTO, size_t n>
inline void GwCLbCT<CRYPTO, n>::Give_ST(UI8* block, UI16 length_last_not_full_block)
{
  UI8 block_var[n / 0x8] = { 0 };

  for (UI8 i = 0; i < n / 0x8; i++)
    block_var[i] = R[l_o_IV - n / 0x8 + i];

  CRYPTO::Give_ST(block_var);

  for (UI8 i = 0; i < l_o_IV - s; i++)
    R[l_o_IV - 0x1 - i] = R[l_o_IV - i - 0x1 - s];

  {
    UI16 temp;
    if (length_last_not_full_block > s)
      temp = s;
    else
      temp = length_last_not_full_block;

    for (UI8 i = 0; i < temp; i++)
    {
      block[i] ^= block_var[i + n / 0x8 - temp];
      R[i] = block[i];
    }
  }
}

template<class CRYPTO, size_t n>
inline void GwCLbCT<CRYPTO, n>::Give_OT(UI8* block, UI16 length_last_not_full_block)
{
  UI8 block_var[n / 0x8] = { 0 };

  for (UI8 i = 0; i < n / 0x8; i++)
    block_var[i] = R[l_o_IV - n / 0x8 + i];

  CRYPTO::Give_ST(block_var);

  for (UI8 i = 0; i < l_o_IV - s; i++)
    R[l_o_IV - 0x1 - i] = R[l_o_IV - i - 0x1 - s];

  {
    UI16 temp;
    if (length_last_not_full_block >= s)
      temp = s;
    else
      temp = length_last_not_full_block;

    for (UI8 i = 0; i < temp; i++)
    {
      R[i] = block[i];
      block[i] ^= block_var[i + n / 0x8 - temp];
    }
  }
}

template<class CRYPTO, size_t n>
inline void GwCLbCT<CRYPTO, n>::push_s(const UI16 s_in)
{
  s = s_in;
}
