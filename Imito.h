#pragma once
#include"abbreviation.h"

template <class CRYPTO, const size_t n>
class Imito:protected CRYPTO
{
public:
  Imito();
  virtual ~Imito();
  
  virtual void imito_step(const UI8* block);
  virtual void imito_final(UI8* block, const UI8 length_of_block_in_byte);
  virtual void imito_final(UI8* block);
  virtual void push_key(const UI8* key_new);

private:
  UI8* block_to_xor;
  UI8* R;
  UI8* K1;
  UI8* K2;

protected:
  virtual bool MSB(const UI8* block);
};

template<class CRYPTO, const size_t n>
inline Imito<CRYPTO, n>::Imito()
{
  block_to_xor = new UI8[n / 0x8];
  K1 = new UI8[n / 0x8];
  K2 = new UI8[n / 0x8];
  R = new UI8[n / 0x8];

  for (UI8 k = 0; k < n / 0x8; ++k)
  {
    R[k] = 0;
    block_to_xor[k] = 0;
  }
}

template<class CRYPTO, const size_t n>
inline Imito<CRYPTO, n>::~Imito()
{
  delete[] R;
  delete[] K1;
  delete[] K2;  
  delete[] block_to_xor;
}

template<class CRYPTO, size_t n>
inline void Imito<CRYPTO, n>::imito_step(const UI8* block)
{
  CRYPTO::xors(block, block_to_xor);
  CRYPTO::Give_ST(block_to_xor);
}

template<class CRYPTO, size_t n>
void Imito<CRYPTO, n>::imito_final(UI8* block, const UI8 length_of_block_in_byte)
{
  if (length_of_block_in_byte != n / 0x8)
  {
    CRYPTO::xors(K2, block_to_xor);
        
    UI8* z;

    z = new UI8[n / 0x8];

    for (UI8 i = 0; i < n / 0x8; i++)
      z[i] = 0;

    for (unsigned char kk = 0; kk < length_of_block_in_byte; ++kk)
      z[n / 0x8 - length_of_block_in_byte + kk] = block[kk];

    z[n / 0x8 - length_of_block_in_byte - 0x1] = 0x80;

    CRYPTO::xors(z, block_to_xor);

    delete[] z;
    CRYPTO::Give_ST(block_to_xor);    

    for (UI8 i = 0; i < n / 0x8; i++)
      block[i] = block_to_xor[i];
  }
  else
    imito_final(block);

}

template<class CRYPTO, size_t n>
void Imito<CRYPTO, n>::imito_final(UI8* block)
{
  CRYPTO::xors(K1, block_to_xor);

  CRYPTO::xors(block, block_to_xor);

  CRYPTO::Give_ST(block_to_xor);

  for (UI8 i = 0; i < n/0x8; i++)
    block[i] = block_to_xor[i];

}

template<class CRYPTO, const size_t n>
void Imito<CRYPTO, n>::push_key(const UI8* key_new)
{

  CRYPTO::push_key(key_new);

  CRYPTO::Give_ST(R);

  UI64* R64;
  R64 = new UI64[n / 0x40];

  for (UI8 k = 0; k < n/0x40; ++k)
    R64[k] = 0;
  for (UI8 z = 0; z < n / 0x40; ++z)
    for (UI8 k = 0; k < 0x8; ++k)
    {
      R64[z] = (R64[z] << 0x8) ^ R[0x8 * z + 0x7 - k];
    }

  if (MSB(R))
  {
    if (n / 0x40 > 0x1)
      for (UI8 z = 0; z < n / 0x40 - 0x1; ++z)
      {
        if (R64[z] & (static_cast<UI64>(0x1) << 0x3f))
          R64[z + 0x1] = (R64[z + 0x1] << 0x1) ^ 0x1;
        else
          R64[z + 0x1] = R64[z + 0x1] << 0x1;
      }

    R64[0] = (R64[0] << 0x1) ^ 0x87;
  }
  else
  {
    if (n / 0x40 > 0x1)
      for (UI8 z = 0; z < n / 0x40 - 0x1; ++z)
      {
        if (R64[z] & (static_cast<UI64>(0x1) << 0x3f))
          R64[z + 0x1] = (R64[z + 0x1] << 0x1) ^ 0x1;
        else
          R64[z + 0x1] = R64[z + 0x1] << 0x1;
      }

    R64[0] = (R64[0] << 0x1);
  }

  for (UI8 k = 0; k < 0x8; ++k)
    for (UI8 z = 0; z < n / 0x40; ++z)
      K1[k+0x8*z]= static_cast<UI8>(R64[z] >> 0x8 * k);

  if (MSB(K1))
  {
    if (n / 0x40 > 0x1)
      for (UI8 z = 0; z < n / 0x40 - 0x1; ++z)
      {
        if (R64[z] & (static_cast<UI64>(0x1) << 0x3f))
          R64[z + 0x1] = (R64[z + 0x1] << 0x1) ^ 0x1;
        else
          R64[z + 0x1] = R64[z + 0x1] << 0x1;
      }

    R64[0] = (R64[0] << 0x1) ^ 0x87;
  }
  else
  {
    if (n / 0x40 > 0x1)
      for (UI8 z = 0; z < n / 0x40 - 0x1; ++z)
      {
        if (R64[z] & (static_cast<UI64>(0x1) << 0x3f))
          R64[z + 0x1] = (R64[z + 0x1] << 0x1) ^ 0x1;
        else
          R64[z + 0x1] = R64[z + 0x1] << 0x1;
      }

    R64[0] = (R64[0] << 0x1);
  }

  for (UI8 k = 0; k < 0x8; ++k)
    for (UI8 z = 0; z < n / 0x40; ++z)
      K2[k + 0x8 * z] = static_cast<unsigned char>(R64[z] >> 0x8 * k);

  for (UI8 k = 0; k < n / 0x8; ++k)
    R[k] = 0;

  delete[] R64;
}

template<class CRYPTO, size_t n>
inline bool Imito<CRYPTO, n>::MSB(const UI8* block)
{
  return block[n/0x8-0x1]&0x80;
}
