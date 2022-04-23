#pragma once
#include "Grass_hopper.h"
class Imito_GH :
  public Grass_hopper
{
public:

  Imito_GH();

  virtual void imito_step(unsigned char* block);
  virtual void imito_final(unsigned char* block, unsigned char length_of_block_in_byte);
  virtual void imito_final(unsigned char* block);
  virtual void push_key(unsigned char* key_new);

protected:

  unsigned char block_to_xor[0x10];
  unsigned char key_imito[0x20];
  virtual bool MSB(unsigned char* block);
};

