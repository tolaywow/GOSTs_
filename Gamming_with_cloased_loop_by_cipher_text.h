#pragma once
#include "Grass_hopper.h"
#define GwCLbCt Gamming_with_cloased_loop_by_cipher_text


class GwCLbCt :
  public Grass_hopper
{
  friend class Test_GwCLbCt;
public:
  GwCLbCt(const unsigned short length_of_IV = 0x20);
  virtual ~GwCLbCt();

  virtual void push_IV(const unsigned char* IV);
  virtual void push_IV_and_key(const unsigned char* IV, const unsigned char* key_new);
  virtual void Give_ST(unsigned char* block);
  virtual void Give_OT(unsigned char* block);
  virtual void Give_ST(unsigned char* block, const unsigned char length_last_not_full_block);
  virtual void Give_OT(unsigned char* block, const unsigned char length_last_not_full_block);
  virtual void push_s(const unsigned short s_in = 0x80);

private:
  unsigned char* block_R;
  unsigned short s, l_o_IV;
};

