#pragma once
#include <cstdint>

/**
 * Шаблон класса режима шифрования "гаммирование", где <class CRYPTO> алгоритм шифрования, <size_t n>
 *
 */
template <class CRYPTO, size_t n>
class Gamming : protected CRYPTO
{
public:
  Gamming(const uint16_t &s = n);
  virtual void push_IV(uint8_t *IV);
  virtual void push_key(uint8_t *key);
  virtual void Give_ST(uint8_t *block);
  virtual void Give_ST(uint8_t *block, const uint16_t &length_of_last_block);
  virtual ~Gamming();

protected:
  virtual void Add();
  virtual void Add(const uint8_t &num);
  virtual void T_r(uint8_t *block, uint8_t *CTR_after_encrypt, const uint16_t &r);

private:
  uint8_t *Gamm;
  uint16_t s;
};

template <class CRYPTO, size_t n>
inline Gamming<CRYPTO, n>::Gamming(const uint16_t &s) : s(s)
{
  Gamm = new uint8_t[n / 0x8];
  for (uint8_t i = 0; i < n / 0x8; ++i)
    Gamm[i] = 0;
}

template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::push_IV(uint8_t *IV)
{
  for (uint8_t i = 0; i < n / 0x10; ++i)
    Gamm[n / 0x10 + i] = IV[i];
}

template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::push_key(uint8_t *key)
{
  CRYPTO::push_key(key);
}

template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::Give_ST(uint8_t *block)
{
  Give_ST(block, s);
}

template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::Give_ST(uint8_t *block, const uint16_t &length_of_last_block)
{
  uint8_t encrypt_block[n / 0x8] = {0};

  for (uint8_t i = 0; i < n / 0x8; i++)
    encrypt_block[i] = Gamm[i];

  CRYPTO::Give_ST(encrypt_block);

  T_r(block, encrypt_block, length_of_last_block);

  Add();
}

template <class CRYPTO, size_t n>
inline Gamming<CRYPTO, n>::~Gamming()
{
  delete[] Gamm;
}

template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::Add()
{
  Add(0);
}

template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::Add(const uint8_t &num)
{
  if (num < n / 0x8)
  {
    ++Gamm[num];
    if (Gamm[num] == 0)
      Add(num + 0x1);
  }
}

template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::T_r(uint8_t *block, uint8_t *CTR_after_encrypt, const uint16_t &r)
{
  for (uint8_t i = 0; i < r / 0x8 - 0x1; i++)
    block[i] ^= CTR_after_encrypt[n / 0x8 - r / 0x8 + i];
  if (r % 0x8 == 0)
    block[r / 0x8 - 0x1] ^= CTR_after_encrypt[n / 0x8 - 0x1];
  else
  {
    uint8_t x = 0x1, z = r % 0x8;

    while (z > 0x1)
    {
      x <<= 0x1;

      x ^= 0x1;

      --z;
    }

    block[r / 0x8 - 0x1] ^= (CTR_after_encrypt[n / 0x8 - 0x1] ^ x);
  }
}
