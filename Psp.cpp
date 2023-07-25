#include "Psp.h"
#include<vector>

Psp::Psp(std::vector<UI8> key, size_t length_of_hash)
{
  length_of_ha = length_of_hash / 0x8;

  h = new UI8[length_of_ha];

  Key = new UI8[length_of_ha];

  for (size_t i = 0; i < length_of_ha; i++)
  {
    Key[i] = 0;
  }

  Facade Facade1(length_of_hash);

  Faca = Facade1;

  for (size_t i = 0; i < ((key.size()<length_of_ha)? key.size(): length_of_ha); i++)
  {    
    Key[length_of_ha-key.size()+i-0x1] = key[i];    
  }
}

Psp::~Psp()
{
  delete[]h;
  delete[]Key;
}

void Psp::generate(UI8* result)
{
    Faca.give_hash(Key, result);

    add_key();
}

void Psp::add_key()
{
  UI8 var = 0x1;

  if (Key[0]+0x1<static_cast<UI16>(Key[0])+0x1)
  {
    var = (static_cast<UI16>(Key[0]) + 0x1) >> 0x8;
  }

  Key[0] += 0x1;

  if (var) 
  {
    for (size_t i = 0x1; i < length_of_ha; i++)
    {
      if (Key[i] + var < static_cast<UI16>(Key[0]) + var)
      {
        Key[i] += var;

        var = (static_cast<UI16>(Key[0]) + 0x1) >> 0x8;
      }
      else
      {
        Key[i] += var;

        var = 0;
      }
    }
  }
}
