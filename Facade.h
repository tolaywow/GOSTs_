#pragma once
#include"abbreviation.h"
#include"Ihash.h"

class Facade
{
public:
  Facade(size_t length_of_hash = 0x200);
  ~Facade();
  void give_hash(UI8* block, UI8* result);

protected:
  Ihash* Hash;
  std::vector<UI8> block_h;
  UI8 length_of_hash_8;
};

