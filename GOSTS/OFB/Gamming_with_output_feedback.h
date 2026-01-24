#pragma once
/**
 * @file Gamming_with_output_feedback.h
 * @author Anatoliy Andreev (tolaywow@gmail.com)
 * @brief Шаблон гаммирования с обратной связью по выходу
 * @version 1.0
 * @date 2026-01-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <cstdint>
#include <vector>
template <class CRYPTO, size_t n>
class Gamming_with_output_feedback : protected CRYPTO
{
public:
  Gamming_with_output_feedback(size_t s, size_t m) : s(s / 0x8), m(m / 0x8) {};
  Gamming_with_output_feedback();
  virtual ~Gamming_with_output_feedback() {};
  virtual void push_IV(const uint8_t *IV);
  void Give_ST(uint8_t *block);
  virtual void push_IV_and_key(const uint8_t *IV, const uint8_t *key_new);

protected:
  size_t s;
  size_t m;
  std::vector<uint8_t> R;
};

// template<class CRYPTO, size_t n>
// inline Gamming_with_output_feedback<CRYPTO, n>::Gamming_with_output_feedback(size_t s, size_t m)
//{
//   this->s = s/8;
//   this->m = m/8;
//
// }

template <class CRYPTO, size_t n>
inline Gamming_with_output_feedback<CRYPTO, n>::Gamming_with_output_feedback()
{
  s = n / 0x8;
  m = n / 0x8;
}

template <class CRYPTO, size_t n>
inline void Gamming_with_output_feedback<CRYPTO, n>::push_IV(const uint8_t *IV)
{
  for (size_t i = 0; i < m; i++)
  {
    R.push_back(IV[i]);
  }
}

template <class CRYPTO, size_t n>
inline void Gamming_with_output_feedback<CRYPTO, n>::Give_ST(uint8_t *block)
{
  uint8_t *l_o_Y;

  l_o_Y = new uint8_t[n / 0x8];

  for (size_t i = 0; i < n / 0x8; i++)
  {
    l_o_Y[i] = R[R.size() - n / 0x8 + i];
  }

  CRYPTO::Give_ST(l_o_Y);

  for (size_t i = R.size() - 0x1; i > (m - n / 0x8) - 0x1; i--)
  {
    R[i] = R[i - (m - n / 0x8)];
  }

  for (size_t i = 0; i < n / 8; i++)
  {
    R[i] = l_o_Y[i];
  }

  for (size_t i = n / 0x8 - s; i < n / 0x8; i++)
  {
    block[i - n / 0x8 + s] ^= l_o_Y[i];
  }

  delete[] l_o_Y;
}

template <class CRYPTO, size_t n>
inline void Gamming_with_output_feedback<CRYPTO, n>::push_IV_and_key(const uint8_t *IV, const uint8_t *key_new)
{
  push_IV(IV);
  CRYPTO::push_key(key_new);
}
