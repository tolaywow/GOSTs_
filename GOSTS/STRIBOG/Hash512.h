#pragma once
// типы подключены в Ihash
#include "Ihash.h"


class Hash512:public Ihash
{
public:
  Hash512();

  ~Hash512() {};

  //length = number of bits
  std::vector<uint8_t> give_hash(uint8_t* text, uint64_t length);

protected:
  uint8_t h[0x40];;
  uint8_t N[0x40];
  uint8_t Summ[0x40];
  uint8_t Keys[0xd][0x40]={0};
  uint8_t _text[0x40]={0};

  void g(uint8_t* text,uint8_t* definition);//N or 0
  void xors(uint8_t* key, uint8_t* block);
  void S(uint8_t* block);
  void P(uint8_t* block);
  void L(uint8_t* block);
  void l(uint64_t* block);
  void Key_create(uint8_t* block);
  void N_();
  void N_(uint16_t length);
  void summ(uint8_t* block);
  void summ(uint16_t length);
  void summ_512(uint8_t* block, uint8_t* summator);
  void E(uint8_t* K, uint8_t* m);
};