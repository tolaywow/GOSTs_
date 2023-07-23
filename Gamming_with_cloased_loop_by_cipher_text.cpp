#include "Gamming_with_cloased_loop_by_cipher_text.h"


GwCLbCt::GwCLbCt(const UI16 length_of_IV):l_o_IV(length_of_IV),
  s(0x80)
{
  block_R = new UI8[length_of_IV];
}

GwCLbCt::~GwCLbCt()
{
  delete[] block_R;
}

void GwCLbCt::push_IV(const UI8* IV)
{
  for (UI8 k = 0; k < l_o_IV; ++k)
  {
    block_R[k] = IV[k];
  }
}

void GwCLbCt::push_IV_and_key(const UI8* IV, const UI8* key_new)
{
  push_IV(IV);
  push_key(key_new);
}

void GwCLbCt::Give_ST(UI8* block)
{
  UI8 blockSR[0x10] = {0};

  for (UI8 k = 0; k < 0x10; ++k)
    blockSR[k] = block_R[l_o_IV - 0x10 + k];

  Grass_hopper::Give_ST(blockSR);

  for (UI8 k = 0; k < 0x10&&k<s/0x8; ++k)
    block[k] ^= blockSR[k];

  for (UI8 k = 0; k < l_o_IV-s/0x8; ++k)
    block_R[l_o_IV - 0x1 - k] = block_R[l_o_IV - k - 0x1-s/0x8];

  for (UI8 k = 0; k < s/0x8; ++k)
    block_R[k] = block[k];

}

void GwCLbCt::Give_OT(UI8* block)
{
  UI8 blockSR[0x10] = {0};

  for (UI8 k = 0; k < 0x10; ++k)
    blockSR[k] = block_R[l_o_IV - 0x10 + k];

  Grass_hopper::Give_ST(blockSR);

  /*for (UI8 k = 0; k < 0x10 && k < s / 0x10; ++k)
    block[k] ^= blockSR[k];*/

  for (UI8 k = 0; k < l_o_IV - s / 0x8; ++k)
    block_R[l_o_IV - 0x1 - k] = block_R[l_o_IV - k - 0x1 - s / 0x8];

  for (UI8 k = 0; k < s / 0x8; ++k)
    block_R[k] = block[k];

  for (UI8 k = 0; k < 0x10 && k < s / 0x8; ++k)
    block[k] ^= blockSR[k];
}

void GwCLbCt::Give_ST(UI8* block,const UI8 length_last_not_full_block)
{
  UI8 block_var[0x10] = { 0 };

  //for (UI8 k = 0; k < length_last_not_full_block; ++k)
  //  block_var[k] = block[k];

  //block_var[length_last_not_full_block] = 0x80;

  Give_ST(block_var);

  for (UI8 k = 0; k < length_last_not_full_block; ++k)
    block[k] ^= block_var[k + 0x10 - length_last_not_full_block];
}

void GwCLbCt::Give_OT(UI8* block, const UI8 length_last_not_full_block)
{
  UI8 block_var[0x10] = { 0 };

  //for (UI8 k = 0; k < length_last_not_full_block; ++k)
  //  block_var[k] = block[k];


  Give_OT(block_var);

  for (UI8 k = 0; k < length_last_not_full_block; ++k)
    block[k] ^= block_var[k + 0x10 - length_last_not_full_block];

}

void GwCLbCt::push_s(const UI16 s_in)
{
  s = s_in;
}
