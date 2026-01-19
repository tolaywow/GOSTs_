#include "Gamming_with_cloased_loop_by_cipher_text.h"

GwCLbCt::GwCLbCt(const uint16_t length_of_IV) : l_o_IV(length_of_IV),
                                            s(0x80)
{
  block_R = new uint8_t[length_of_IV];
}

GwCLbCt::~GwCLbCt()
{
  delete[] block_R;
}

void GwCLbCt::push_IV(const uint8_t *IV)
{
  for (uint8_t k = 0; k < l_o_IV; ++k)
  {
    block_R[k] = IV[k];
  }
}

void GwCLbCt::push_IV_and_key(const uint8_t *IV, const uint8_t *key_new)
{
  push_IV(IV);
  push_key(key_new);
}

void GwCLbCt::Give_ST(uint8_t *block)
{
  uint8_t blockSR[0x10] = {0};

  for (uint8_t k = 0; k < 0x10; ++k)
    blockSR[k] = block_R[l_o_IV - 0x10 + k];

  Grass_hopper::Give_ST(blockSR);

  for (uint8_t k = 0; k < 0x10 && k < s / 0x8; ++k)
    block[k] ^= blockSR[k];

  for (uint8_t k = 0; k < l_o_IV - s / 0x8; ++k)
    block_R[l_o_IV - 0x1 - k] = block_R[l_o_IV - k - 0x1 - s / 0x8];

  for (uint8_t k = 0; k < s / 0x8; ++k)
    block_R[k] = block[k];
}

void GwCLbCt::Give_OT(uint8_t *block)
{
  uint8_t blockSR[0x10] = {0};

  for (uint8_t k = 0; k < 0x10; ++k)
    blockSR[k] = block_R[l_o_IV - 0x10 + k];

  Grass_hopper::Give_ST(blockSR);

  /*for (uint8_t k = 0; k < 0x10 && k < s / 0x10; ++k)
    block[k] ^= blockSR[k];*/

  for (uint8_t k = 0; k < l_o_IV - s / 0x8; ++k)
    block_R[l_o_IV - 0x1 - k] = block_R[l_o_IV - k - 0x1 - s / 0x8];

  for (uint8_t k = 0; k < s / 0x8; ++k)
    block_R[k] = block[k];

  for (uint8_t k = 0; k < 0x10 && k < s / 0x8; ++k)
    block[k] ^= blockSR[k];
}

void GwCLbCt::Give_ST(uint8_t *block, const uint8_t length_last_not_full_block)
{
  uint8_t block_var[0x10] = {0};

  // for (uint8_t k = 0; k < length_last_not_full_block; ++k)
  //   block_var[k] = block[k];

  // block_var[length_last_not_full_block] = 0x80;

  Give_ST(block_var);

  for (uint8_t k = 0; k < length_last_not_full_block; ++k)
    block[k] ^= block_var[k + 0x10 - length_last_not_full_block];
}

void GwCLbCt::Give_OT(uint8_t *block, const uint8_t length_last_not_full_block)
{
  uint8_t block_var[0x10] = {0};

  // for (uint8_t k = 0; k < length_last_not_full_block; ++k)
  //   block_var[k] = block[k];

  Give_OT(block_var);

  for (uint8_t k = 0; k < length_last_not_full_block; ++k)
    block[k] ^= block_var[k + 0x10 - length_last_not_full_block];
}

void GwCLbCt::push_s(const uint16_t s_in)
{
  s = s_in;
}
