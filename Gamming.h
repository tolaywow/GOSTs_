#pragma once
#include"abbreviation.h"

template <class CRYPTO, size_t n>
class Gamming:protected CRYPTO
{
public:
  Gamming(const UI16& s=n);
  virtual void push_IV(UI8* IV);
  virtual void push_key(UI8* key);
  virtual void Give_ST(UI8* block);
  virtual void Give_ST(UI8* block,const UI16& length_of_last_block);
  virtual ~Gamming();
protected:
  virtual void Add();
  virtual void Add(const UI8& num);
  virtual void T_r(UI8* block, UI8* CTR_after_encrypt, const UI16& r);
private:
  UI8* Gamm;  
  UI16 s;

};

template<class CRYPTO, size_t n>
inline Gamming<CRYPTO, n>::Gamming(const UI16& s) :s(s)
{
  Gamm = new UI8[n / 0x8];
  for (UI8 i = 0; i < n / 0x8; ++i)
    Gamm[i] = 0;
}

template<class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::push_IV(UI8* IV)
{
  for (UI8 i = 0; i < n / 0x10; ++i)
    Gamm[n / 0x10 + i] = IV[i];
}

template<class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::push_key(UI8* key)
{
  CRYPTO::push_key(key);
}

template<class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::Give_ST(UI8* block)
{
  Give_ST(block, s);
}

template<class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::Give_ST(UI8* block, const UI16& length_of_last_block)
{
  UI8 encrypt_block[n / 0x8] = { 0 };

  for (UI8 i = 0; i < n / 0x8; i++)
    encrypt_block[i] = Gamm[i];

  CRYPTO::Give_ST(encrypt_block);

  T_r(block, encrypt_block, length_of_last_block);

  Add();
}

template<class CRYPTO, size_t n>
inline Gamming<CRYPTO, n>::~Gamming()
{
  delete[] Gamm;
}

template<class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::Add()
{
  Add(0);
}

template<class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::Add(const UI8& num)
{
  if (num < n / 0x8)
  {
    ++Gamm[num];
    if (Gamm[num] == 0)
      Add(num + 0x1);
  }
}

template<class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::T_r(UI8* block, UI8* CTR_after_encrypt, const UI16& r)
{
  for (UI8 i = 0; i < r / 0x8 - 0x1; i++)
    block[i] ^= CTR_after_encrypt[n / 0x8 - r / 0x8 + i];
  if (r % 0x8 == 0)
    block[r / 0x8 - 0x1] ^= CTR_after_encrypt[n / 0x8 - 0x1];
  else
  {
    UI8 x = 0x1, z = r % 0x8;

    while (z > 0x1)
    {
      x <<= 0x1;

      x ^= 0x1;

      --z;
    }

    block[r / 0x8 - 0x1] ^= (CTR_after_encrypt[n / 0x8 - 0x1] ^ x);
  }
}
