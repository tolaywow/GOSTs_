#pragma once
#include"abbreviation.h"
#include <vector>
template <class CRYPTO, size_t n>
class Gamming_with_output_feedback :protected CRYPTO
{
public:
  Gamming_with_output_feedback(size_t s, size_t m) : s(s/0x8), m(m/0x8) {};
  Gamming_with_output_feedback();
  virtual ~Gamming_with_output_feedback() {};
  virtual void push_IV(UI8* IV);
  void Give_ST(UI8* block);
  virtual void push_IV_and_key(const UI8* IV, const UI8* key_new);
protected:
  size_t s;
  size_t m;
  std::vector<UI8> R;
  

};

//template<class CRYPTO, size_t n>
//inline Gamming_with_output_feedback<CRYPTO, n>::Gamming_with_output_feedback(size_t s, size_t m)
//{
//  this->s = s;
//  this->m = m;
//
//}

template<class CRYPTO, size_t n>
inline Gamming_with_output_feedback<CRYPTO, n>::Gamming_with_output_feedback()
{
  s = n/0x8;
  m = n/0x8;
}

template<class CRYPTO, size_t n>
inline void Gamming_with_output_feedback<CRYPTO, n>::push_IV(UI8* IV)
{
  for (size_t i = 0; i < m; i++)
  {
    R.push_back(IV[i]);
  }
}

template<class CRYPTO, size_t n>
inline void Gamming_with_output_feedback<CRYPTO, n>::Give_ST(UI8* block)
{
  std::vector<UI8> l_o_Y;

  for (size_t i = 0; i < n/0x8; i++)
  {
    l_o_Y.push_back(R[m - 0x1 - n / 0x8 + i]);
  }

  CRYPTO::Give_ST(l_o_Y);

  for (size_t i = R.size()-0x1; i > n/0x8-0x1; i--)
  {
    R[i] = R[i-n/0x8- 0x1];
  }
  for (size_t i = 0; i < n/8; i++)
  {
    R[i] = l_o_Y[i];
  }

  for (size_t i = n/0x8-s; i <n/0x8; i++)
  {
    block[i - n / 0x8 + s] = l_o_Y[i];
  }
}

template<class CRYPTO, size_t n>
inline void Gamming_with_output_feedback<CRYPTO, n>::push_IV_and_key(const UI8* IV, const UI8* key_new)
{
  push_IV(IV);
  CRYPTO::push_key(key_new);  

}
