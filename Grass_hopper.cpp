#include "Grass_hopper.h"
#include<iostream>

namespace GH_pish
{
  unsigned char pi[] =
  {
      0XFC, 0XEE, 0XDD, 0X11, 0XCF, 0X6E, 0X31, 0X16,
      0XFB, 0XC4, 0XFA, 0XDA, 0X23, 0XC5, 0X04, 0X4D,
      0XE9, 0X77, 0XF0, 0XDB, 0X93, 0X2E, 0X99, 0XBA,
      0X17, 0X36, 0XF1, 0XBB, 0X14, 0XCD, 0X5F, 0XC1,
      0XF9, 0X18, 0X65, 0X5A, 0XE2, 0X5C, 0XEF, 0X21,
      0X81, 0X1C, 0X3C, 0X42, 0X8B, 0X01, 0X8E, 0X4F,
      0X05, 0X84, 0X02, 0XAE, 0XE3, 0X6A, 0X8F, 0XA0,
      0X06, 0X0B, 0XED, 0X98, 0X7F, 0XD4, 0XD3, 0X1F,
      0XEB, 0X34, 0X2C, 0X51, 0XEA, 0XC8, 0X48, 0XAB,
      0XF2, 0X2A, 0X68, 0XA2, 0XFD, 0X3A, 0XCE, 0XCC,
      0XB5, 0X70, 0X0E, 0X56, 0X08, 0X0C, 0X76, 0X12,
      0XBF, 0X72, 0X13, 0X47, 0X9C, 0XB7, 0X5D, 0X87,
      0X15, 0XA1, 0X96, 0X29, 0X10, 0X7B, 0X9A, 0XC7,
      0XF3, 0X91, 0X78, 0X6F, 0X9D, 0X9E, 0XB2, 0XB1,
      0X32, 0X75, 0X19, 0X3D, 0XFF, 0X35, 0X8A, 0X7E,
      0X6D, 0X54, 0XC6, 0X80, 0XC3, 0XBD, 0X0D, 0X57,
      0XDF, 0XF5, 0X24, 0XA9, 0X3E, 0XA8, 0X43, 0XC9,
      0XD7, 0X79, 0XD6, 0XF6, 0X7C, 0X22, 0XB9, 0X03,
      0XE0, 0X0F, 0XEC, 0XDE, 0X7A, 0X94, 0XB0, 0XBC,
      0XDC, 0XE8, 0X28, 0X50, 0X4E, 0X33, 0X0A, 0X4A, 
      0XA7, 0X97, 0X60, 0X73, 0X1E, 0X00, 0X62, 0X44,
      0X1A, 0XB8, 0X38, 0X82, 0X64, 0X9F, 0X26, 0X41,
      0XAD, 0X45, 0X46, 0X92, 0X27, 0X5E, 0X55, 0X2F,
      0X8C, 0XA3, 0XA5, 0X7D, 0X69, 0XD5, 0X95, 0X3B,
      0X07, 0X58, 0XB3, 0X40, 0X86, 0XAC, 0X1D, 0XF7,
      0X30, 0X37, 0X6B, 0XE4, 0X88, 0XD9, 0XE7, 0X89,
      0XE1, 0X1B, 0X83, 0X49, 0X4C, 0X3F, 0XF8, 0XFE,
      0X8D, 0X53, 0XAA, 0X90, 0XCA, 0XD8, 0X85, 0X61,
      0X20, 0X71, 0X67, 0XA4, 0X2D, 0X2B, 0X09, 0X5B,
      0XCB, 0X9B, 0X25, 0XD0, 0XBE, 0XE5, 0X6C, 0X52,
      0X59, 0XA6, 0X74, 0XD2, 0XE6, 0XF4, 0XB4, 0XC0,
      0XD1, 0X66, 0XAF, 0XC2, 0X39, 0X4B, 0X63, 0XB6
  };
 
  unsigned char pish[] =
  {
      0XA5, 0X2D, 0X32, 0X8F, 0X0E, 0X30, 0X38, 0XC0, 
      0X54, 0XE6, 0X9E, 0X39, 0X55, 0X7E, 0X52, 0X91,
      0X64, 0X03, 0X57, 0X5A, 0X1C, 0X60, 0X07, 0X18, 
      0X21, 0X72, 0XA8, 0XD1, 0X29, 0XC6, 0XA4, 0X3F,
      0XE0, 0X27, 0X8D, 0X0C, 0X82, 0XEA, 0XAE, 0XB4,
      0X9A, 0X63, 0X49, 0XE5, 0X42, 0XE4, 0X15, 0XB7,
      0XC8, 0X06, 0X70, 0X9D, 0X41, 0X75, 0X19, 0XC9,
      0XAA, 0XFC, 0X4D, 0XBF, 0X2A, 0X73, 0X84, 0XD5,
      0XC3, 0XAF, 0X2B, 0X86, 0XA7, 0XB1, 0XB2, 0X5B,
      0X46, 0XD3, 0X9F, 0XFD, 0XD4, 0X0F, 0X9C, 0X2F,
      0X9B, 0X43, 0XEF, 0XD9, 0X79, 0XB6, 0X53, 0X7F,
      0XC1, 0XF0, 0X23, 0XE7, 0X25, 0X5E, 0XB5, 0X1E,
      0XA2, 0XDF, 0XA6, 0XFE, 0XAC, 0X22, 0XF9, 0XE2, 
      0X4A, 0XBC, 0X35, 0XCA, 0XEE, 0X78, 0X05, 0X6B,
      0X51, 0XE1, 0X59, 0XA3, 0XF2, 0X71, 0X56, 0X11,
      0X6A, 0X89, 0X94, 0X65, 0X8C, 0XBB, 0X77, 0X3C,
      0X7B, 0X28, 0XAB, 0XD2, 0X31, 0XDE, 0XC4, 0X5F,
      0XCC, 0XCF, 0X76, 0X2C, 0XB8, 0XD8, 0X2E, 0X36,
      0XDB, 0X69, 0XB3, 0X14, 0X95, 0XBE, 0X62, 0XA1,
      0X3B, 0X16, 0X66, 0XE9, 0X5C, 0X6C, 0X6D, 0XAD, 
      0X37, 0X61, 0X4B, 0XB9, 0XE3, 0XBA, 0XF1, 0XA0,
      0X85, 0X83, 0XDA, 0X47, 0XC5, 0XB0, 0X33, 0XFA,
      0X96, 0X6F, 0X6E, 0XC2, 0XF6, 0X50, 0XFF, 0X5D,
      0XA9, 0X8E, 0X17, 0X1B, 0X97, 0X7D, 0XEC, 0X58,
      0XF7, 0X1F, 0XFB, 0X7C, 0X09, 0X0D, 0X7A, 0X67,
      0X45, 0X87, 0XDC, 0XE8, 0X4F, 0X1D, 0X4E, 0X04,
      0XEB, 0XF8, 0XF3, 0X3E, 0X3D, 0XBD, 0X8A, 0X88,
      0XDD, 0XCD, 0X0B, 0X13, 0X98, 0X02, 0X93, 0X80,
      0X90, 0XD0, 0X24, 0X34, 0XCB, 0XED, 0XF4, 0XCE, 
      0X99, 0X10, 0X44, 0X40, 0X92, 0X3A, 0X01, 0X26,
      0X12, 0X1A, 0X48, 0X68, 0XF5, 0X81, 0X8B, 0XC7,
      0XD6, 0X20, 0X0A, 0X08, 0X00, 0X4C, 0XD7, 0X74
  };
}

Grass_hopper::Grass_hopper()
{
  for (unsigned char k = 0; k < sizeof(key); ++k)
  {
    key[k] = 0;
  }
  
  Form_Key();
}

Grass_hopper::~Grass_hopper()
{

}

void Grass_hopper::push_key(unsigned char* key_new)
{

  for (unsigned char k = 0; k < 0x20; ++k)
  {
    key[k] = key_new[k];
  }

  Form_Key();
}

void Grass_hopper::Give_ST(unsigned char* block)
{
  for (unsigned char k = 0; k < 0x9; ++k)
  {
    xors(keys[k], block);
    S_p(block);
    L_p(block);
  }

  xors(keys[0x9], block);
}

void Grass_hopper::Give_OT(unsigned char* block)
{
  //xors(keys[0x9], block);

  for (unsigned char k = 0; k < 0x9; ++k)
  {
    xors(keys[0x9 - k], block);
    L_l(block);
    S_l(block);   
  }
  xors(keys[0], block);
}

void Grass_hopper::xors(unsigned __int8* Key, unsigned __int8* block)
{
  for (unsigned char k = 0; k < 0x10; ++k)
  {
    block[k] ^= Key[k];
  }
}

void Grass_hopper::S_p(unsigned char* block)
{
  for (unsigned char k = 0; k < 0x10; ++k)
  {
    block[k] = GH_pish::pi[block[k]];
  }
}

void Grass_hopper::S_l(unsigned char* block)
{
  for (unsigned char k = 0; k < 0x10; ++k)
  {
    block[k] = GH_pish::pish[block[k]];
  }
}

unsigned char Grass_hopper::l(unsigned char* block)
{
  unsigned int l_mass[] = {
    0x01, 0x94, 0x20, 0x85,
    0x10, 0xc2, 0xc0, 0x01,
    0xfb, 0x01, 0xc0, 0xc2,
    0x10, 0x85, 0x20, 0x94 };

  int a0 = 0;
  const int px = 0x1c3;
  for (char i = 0; i < 0x10; ++i)
  {
    if (block[i] != 0)
    {
      for (char j = 0; j < 0x8; ++j)
        if ((l_mass[i] ^ (1 << j)) < l_mass[i])
          a0 ^= (block[i] << j);
    }
  }
  for (int i = 0x7; i > 0; i--)
    if ((a0 ^ (0x1 << (i + 0x7))) < a0)
      a0 ^= (px << (i - 0x1));

  return a0;
}

void Grass_hopper::L_p(unsigned char* block)
{
  for (unsigned char k = 0; k < 0x10; ++k)
  {
    unsigned char a0 = l(block);

    for (unsigned char i = 0; i < 0x0f; ++i)
    {
      block[i] = block[i + 0x1];
    }

    block[0x0f] = a0;
  }
}

void Grass_hopper::L_l(unsigned char* block)
{
  for (unsigned char k = 0; k < 0x10; ++k)
  {
    unsigned char var = block[0x0f];

    for (int j = 0x0f; j > 0; --j)
    {
      block[j] = block[j - 1];
    }

    block[0] = var;
    block[0] = l(block);
  }
}

void Grass_hopper::key_new(unsigned char* key1, unsigned char* key2, unsigned char numkey)
{
  for (unsigned char i = 0x1; i < 0x9; ++i)
  {
    unsigned char key_n1[0x10];

    for (unsigned char j = 0; j < 0x10; ++j)
      key_n1[j] = key1[j];

    unsigned char C[0x10];

    for (unsigned char j = 0x1; j < 0x10; ++j)
      C[j] = 0;

    C[0] = 0x8 * (numkey - 0x1) + i;

    L_p(C);
    xors(C, key1);
    S_p(key1);
    L_p(key1);
    xors(key2, key1);

    for (char j = 0; j < 0x10; ++j)
      key2[j] = key_n1[j];
  }
}

void Grass_hopper::Form_Key()
{
  for (unsigned char k = 0; k < 0x10; ++k)
  {
    keys[0][k]= key[0x10 + k];

    keys[0x1][k] = key[k];
  }

  for (unsigned char k = 0x1; k < 0x5; ++k)
  {
    for (unsigned char i = 0; i < 0x10; ++i)
    {
      keys[k * 0x2][i] = keys[k * 0x2 - 0x2][i];

      keys[k * 0x2 + 0x1][i] = keys[k * 0x2 - 0x1][i];
    }
    key_new(keys[k * 0x2], keys[k * 0x2 + 0x1], k);
  }
}
