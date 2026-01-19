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

  virtual void push_IV(const UI8* IV);
  virtual void push_IV_and_key(const UI8* IV, const UI8* key_new);
  virtual void Give_ST(UI8* block);
  virtual void Give_OT(UI8* block);
  virtual void Give_ST(UI8* block, const UI8 length_last_not_full_block);
  virtual void Give_OT(UI8* block, const UI8 length_last_not_full_block);
  virtual void push_s(const unsigned short s_in = 0x80);

private:
  UI8* block_R;
  unsigned short s, l_o_IV;
};

