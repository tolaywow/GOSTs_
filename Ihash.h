#pragma once
#include"abbreviation.h"
#include <vector>

class Ihash
{
public:
  virtual ~Ihash(){} /*= 0*/;
  virtual std::vector<UI8> give_hash(UI8* text, UI64 length) = 0;
};


