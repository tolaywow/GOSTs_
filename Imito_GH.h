#pragma once
#include "Grass_hopper.h"

class Imito_GH :
  public Grass_hopper
{
  friend class Test_imito;
public:
  Imito_GH();

  virtual void imito_step(const UI8* block);
  virtual void imito_final(UI8* block, const UI8 length_of_block_in_byte);
  virtual void imito_final(UI8* block);
  virtual void push_key(const UI8* key_new);

private:
  UI8 block_to_xor[0x10];
  UI8 key_imito[0x20];

protected:
  virtual bool MSB(const UI8* block);
};

