#pragma once
#include"abbreviation.h"
#include"Facade.h"
#include<vector>

class Psp
{
public:
  Psp(std::vector<UI8> key,size_t length_of_hash=0x200);
  ~Psp();
  void generate(UI8* result);
protected:
  UI8* h;
  UI8* Key;
  size_t length_of_ha;
  Facade Faca;
  void add_key();
};

