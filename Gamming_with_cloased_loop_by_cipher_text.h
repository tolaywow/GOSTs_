#pragma once
#include "Grass_hopper.h"

#define GwCLbCt Gamming_with_cloased_loop_by_cipher_text


class GwCLbCt :
    public Grass_hopper
{
public:
 //GwCLbCt();
  GwCLbCt(unsigned int length_of_IV);

  void push_key(unsigned char* key_new);
  void push_IV(unsigned char* IV);
  void Give_ST(unsigned char* block);
protected:



  unsigned char* block_R;
};

