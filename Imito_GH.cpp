#include "Imito_GH.h"

Imito_GH::Imito_GH()
{
  for (unsigned char k = 0; k < 0x10; ++k)
    block_to_xor[k] = 0;
}

void Imito_GH::imito_step(const unsigned char* block)
{
  xors(block, block_to_xor);

  Give_ST(block_to_xor);
}

void Imito_GH::imito_final(unsigned char* block,const unsigned char length_of_block_in_byte)
{
  if (length_of_block_in_byte != 0x10)
  {
    xors(key_imito + 0x10, block_to_xor);

    unsigned char z[0x10] = {0};

    for (unsigned char k = 0; k <length_of_block_in_byte; ++k)     
        z[0x10 - length_of_block_in_byte+k] = block[k];  

    z[0x10 - length_of_block_in_byte - 0x1] = 0x80;

    xors(z, block_to_xor);

    Give_ST(block_to_xor);

    for (unsigned char k = 0; k < 0x10; ++k)
      block[k] = block_to_xor[k];
  }
  else
    imito_final(block);
}

void Imito_GH::imito_final(unsigned char* block)
{
  xors(key_imito, block_to_xor);

  xors(block, block_to_xor);

  Give_ST(block_to_xor);

  for (unsigned char k = 0; k < 0x10; ++k)
    block[k] = block_to_xor[k];
}

void Imito_GH::push_key(const unsigned char* key_new)
{
  Grass_hopper::push_key(key_new);

  unsigned char R[0x10] = { 0 };

  Give_ST(R);

  unsigned __int64 R64[0x2] = { 0 };

  
  for (unsigned char k = 0; k < 0x8; ++k)
  {
    R64[0] = (R64[0] << 0x8) ^ R[0x7 - k];
    R64[0x1] = (R64[0x1] << 0x8) ^ R[0xf - k];
  }

  if (MSB(R))
  {
    if (R64[0] & (unsigned __int64(0x1) << 0x3f))
      R64[0x1] = (R64[0x1] << 0x1) ^ 0x1;
    else
      R64[0x1] = R64[0x1] << 0x1;

    R64[0] = (R64[0]<<0x1)^0x87;
  }   
  else
  {
    if (R64[0]&( unsigned __int64(0x1) << 0x3f))
      R64[0x1] = R64[0x1] << 0x1 ^ 0x1;
    else
      R64[0x1] = R64[0x1] << 0x1;

    R64[0] = R64[0] << 0x1;
  }

  for (unsigned char k = 0; k < 0x8; ++k)
  {
    key_imito[k] = static_cast<unsigned char>(R64[0] >> 0x8 * k);
    key_imito[k+0x8]= static_cast<unsigned char>(R64[0x1] >> 0x8 * k);
  }

  if (MSB(key_imito))
  {
    if (R64[0] & (unsigned __int64(0x1) << 0x3f))
      R64[0x1] = R64[0x1] << 0x1 ^ 0x1;
    else
      R64[0x1] = R64[0x1] << 0x1;

    R64[0] = (R64[0] << 1) ^ 0x87;
  }
  else
  {
    if (R64[0] & (unsigned __int64(0x1) << 0x3f))
      R64[0x1] = R64[0x1] << 0x1 ^ 0x1;
    else
      R64[0x1] = (R64[0x1] << 0x1);

    R64[0] = R64[0] << 0x1;

  }

  for (unsigned char k = 0; k < 0x8; ++k)
  {
    key_imito[k+0x10] = static_cast<unsigned char>(R64[0] >> 0x8 * k);
    key_imito[k + 0x18] = static_cast<unsigned char>(R64[0x1] >> 0x8 * k);
  }
}

bool Imito_GH::MSB(const unsigned char* block)
{
  return block[0xf]&0x80;
}
