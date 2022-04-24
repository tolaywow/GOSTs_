#pragma once
#include "Grass_hopper.h"

#define GwCLbCt Gamming_with_cloased_loop_by_cipher_text


class GwCLbCt :
    public Grass_hopper
{
public:
 //GwCLbCt();
  GwCLbCt(unsigned short length_of_IV=0x40);
  ~GwCLbCt();

  
  virtual void push_IV(unsigned char* IV);
  virtual void push_IV_and_key(unsigned char* IV, unsigned char* key_new);
  virtual void Give_ST(unsigned char* block);
  virtual void Give_OT(unsigned char* block);
  virtual void Give_ST(unsigned char* block, unsigned char length_last_not_full_block);
  virtual void Give_OT(unsigned char* block, unsigned char length_last_not_full_block);
  virtual void push_s(unsigned short s_in = 0x100);

protected:

  unsigned char* block_R;
  unsigned short s, l_o_IV;

};

