#include "Gamming_with_cloased_loop_by_cipher_text.h"

#define UC unsigned char

GwCLbCt::GwCLbCt(unsigned short length_of_IV)
{
  block_R = new UC[length_of_IV];
  l_o_IV = length_of_IV;
  push_s();
}

GwCLbCt::~GwCLbCt()
{
  delete[] block_R;
}

void GwCLbCt::push_IV(unsigned char* IV)
{
  for (UC k = 0; k < l_o_IV; ++k)
  {
    block_R[k] = IV[k];
  }
}

void GwCLbCt::push_IV_and_key(unsigned char* IV, unsigned char* key_new)
{
  push_IV(IV);
  push_key(key_new);
}

void GwCLbCt::Give_ST(unsigned char* block)
{
  UC blockSR[0x10];

  for (UC k = 0; k < 0x10; ++k)
    blockSR[k] = block_R[l_o_IV - 0x10 + k];

  Grass_hopper::Give_ST(blockSR);

  for (UC k = 0; k < 0x10&&k<s/0x10; ++k)
    block[k] ^= blockSR[k];

  for (UC k = 0; k < l_o_IV-s/0x10; ++k)
    block_R[l_o_IV - 0x1 - k] = block_R[l_o_IV - k - 0x1-s/0x10];

  for (UC k = 0; k < s/0x10; ++k)
    block_R[k] = blockSR[k];

}

void GwCLbCt::Give_OT(unsigned char* block)
{
  UC blockSR[0x10];

  for (UC k = 0; k < 0x10; ++k)
    blockSR[k] = block_R[l_o_IV - 0x10 + k];

  Grass_hopper::Give_ST(blockSR);

  for (UC k = 0; k < 0x10 && k < s / 0x10; ++k)
    block[k] ^= blockSR[k];

  for (UC k = 0; k < l_o_IV - s / 0x10; ++k)
    block_R[l_o_IV - 0x1 - k] = block_R[l_o_IV - k - 0x1 - s / 0x10];

  for (UC k = 0; k < s / 0x10; ++k)
    block_R[k] = block[k];

  for (UC k = 0; k < 0x10 && k < s / 0x10; ++k)
    block[k] ^= blockSR[k];
}

void GwCLbCt::Give_ST(unsigned char* block, unsigned char length_last_not_full_block)
{
  UC block_var[0x10] = { 0 };

  //for (UC k = 0; k < length_last_not_full_block; ++k)
  //  block_var[k] = block[k];

  //block_var[length_last_not_full_block] = 0x80;

  Give_ST(block_var);

  for (UC k = 0; k < length_last_not_full_block; ++k)
    block[k] ^= block_var[k];  
}

void GwCLbCt::Give_OT(unsigned char* block, unsigned char length_last_not_full_block)
{
  UC block_var[0x10] = { 0 };

  //for (UC k = 0; k < length_last_not_full_block; ++k)
  //  block_var[k] = block[k];


  Give_OT(block_var);

  for (UC k = 0; k < length_last_not_full_block; ++k)
    block[k] ^= block_var[k];

}

void GwCLbCt::push_s(unsigned short s_in)
{
  s = s_in;
}
