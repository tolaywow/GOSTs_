#pragma once
#pragma once
#include"abbreviation.h"

class Hash512
{
public:
  Hash512();
  //length = number of bits
  UI8* give_hash(UI8* text,UI64 length);

protected:
  UI8 h[0x40];
  UI8 N[0x40];
  UI8 Summ[0x40];
  UI8 Keys[0xd][0x40];

  void g(UI8* text,UI8* definition);//N or 0

  void xors(UI8* key, UI8* block);
  void S(UI8* block);
  void P(UI8* block);
  void L(UI8* block);
  void l(UI64* block);
  void Key_create();

};