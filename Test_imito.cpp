#include "Test_imito.h"

#define UC unsigned char

Test_imito::Test_imito()
{
  UC key[0x20];

  {
    UC key_r[] =
    {
      0x88, 0x99, 0xaa, 0xbb,
      0xcc, 0xdd, 0xee, 0xff,
      0x00, 0x11, 0x22, 0x33,
      0x44, 0x55, 0x66, 0x77,
      0xfe, 0xdc, 0xba, 0x98,
      0x76, 0x54, 0x32, 0x10,
      0x01, 0x23, 0x45, 0x67,
      0x89, 0xab, 0xcd, 0xef
    };

    for (UC k = 0; k < 0x20; ++k)
      key[k] = key_r[0x1f - k];
  }

  push_key(key);
}

bool Test_imito::result_of_testing(bool* mass)
{
  bool result = true;

  if (!(mass[0] = test_R()))
    result = false;
  if (!(mass[0x1] = test_MSBR()))  
    result = false;
  if (!(mass[0x2] = test_K1()))
    result = false;
  if (!(mass[0x3] = test_MSBK1()))
    result = false;
  if (!(mass[0x4] = test_K2()))
    result = false;
  if (!(mass[0x5] = test_P()))
    result = false;
  if (!(mass[0x6] = test_P_not_full()))
    result = false;

  return result;
}

bool Test_imito::result_of_testing()
{
  bool mass[0x10];

  return result_of_testing(mass);
}

bool Test_imito::test_R()
{
  UC R[0x10] = { 0 };

  Give_ST(R);

  UC R_con[] =
  {
    0x94, 0xbe, 0xc1, 0x5e,
    0x26, 0x9c, 0xf1, 0xe5,
    0x06, 0xf0, 0x2b, 0x99,
    0x4c, 0x0a, 0x8e, 0xa0
  };

  for (UC k = 0; k < 0x10; ++k)
    if (!(R_con[k] == R[0xf - k]))
      return false;

  return true;
}

bool Test_imito::test_MSBR()
{
  UC R[0x10];

  {
    UC R_r[] =
    {
      0x94, 0xbe, 0xc1, 0x5e,
      0x26, 0x9c, 0xf1, 0xe5,
      0x06, 0xf0, 0x2b, 0x99,
      0x4c, 0x0a, 0x8e, 0xa0
    };

    for (UC k = 0; k < 0x10; ++k)
      R[k] = R_r[0xf - k];
  }

  if (!MSB(R))
    return false;

  return true;
}

bool Test_imito::test_K1()
{
  UC key[0x20];
  UC key_cons[]=
  {
      0x29, 0x7d, 0x82, 0xbc,
      0x4d, 0x39, 0xe3, 0xca,
      0x0d, 0xe0, 0x57, 0x32,
      0x98, 0x15, 0x1d, 0xc7
  };

  {
    UC key_r[] =
    {
      0x88, 0x99, 0xaa, 0xbb,
      0xcc, 0xdd, 0xee, 0xff,
      0x00, 0x11, 0x22, 0x33,
      0x44, 0x55, 0x66, 0x77,
      0xfe, 0xdc, 0xba, 0x98,
      0x76, 0x54, 0x32, 0x10,
      0x01, 0x23, 0x45, 0x67,
      0x89, 0xab, 0xcd, 0xef
    };

    for (UC k = 0; k < 0x20; ++k)
      key[k] = key_r[0x1f - k];
  }

  push_key(key);

  for (UC k = 0; k < 0x10; ++k)
    if (key_imito[k] != key_cons[0xf - k])
      return false;

  return true;
}

bool Test_imito::test_MSBK1()
{
  UC K1[0x10];

  {
    UC K1_r[] =
    {
      0x29, 0x7d, 0x82, 0xbc,
      0x4d, 0x39, 0xe3, 0xca,
      0x0d, 0xe0, 0x57, 0x32,
      0x98, 0x15, 0x1d, 0xc7
    };

    for (UC k = 0; k < 0x10; ++k)
      K1[k] = K1_r[0xf - k];
  }

  if (MSB(K1))
    return false;

  return true;
}

bool Test_imito::test_K2()
{
  UC key[0x20];
  UC key_cons[] =
  {
      0x52, 0xfb, 0x05, 0x78,
      0x9a, 0x73, 0xc7, 0x94,
      0x1b, 0xc0, 0xae, 0x65,
      0x30, 0x2a, 0x3b, 0x8e
  };

  {
    UC key_r[] =
    {
      0x88, 0x99, 0xaa, 0xbb,
      0xcc, 0xdd, 0xee, 0xff,
      0x00, 0x11, 0x22, 0x33,
      0x44, 0x55, 0x66, 0x77,
      0xfe, 0xdc, 0xba, 0x98,
      0x76, 0x54, 0x32, 0x10,
      0x01, 0x23, 0x45, 0x67,
      0x89, 0xab, 0xcd, 0xef
    };

    for (UC k = 0; k < 0x20; ++k)
      key[k] = key_r[0x1f - k];
  }

  push_key(key);

  for (UC k = 0; k < 0x10; ++k)
    if (key_imito[k+0x10] != key_cons[0xf - k])
      return false;


  return true;
}

bool Test_imito::test_P()
{
  //P1
  {
    UC P1[0x10];

    {
      UC P1_r[] =
      {
        0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x00,
        0xff, 0xee, 0xdd, 0xcc,
        0xbb, 0xaa, 0x99, 0x88
      };

      for (UC k = 0; k < 0x10; ++k)
        P1[k] = P1_r[0xf - k];
    }

    imito_step(P1);

    UC OB[] =
    {
      0x7f, 0x67, 0x9d, 0x90,
      0xbe, 0xbc, 0x24, 0x30,
      0x5a, 0x46, 0x8d, 0x42,
      0xb9, 0xd4, 0xed, 0xcd
    };

    for (UC k = 0; k < 0x10; ++k)
      if (block_to_xor[k] != OB[0xf - k])
        return false;
  }

  //P2
  {
    UC P2[0x10];

    {
      UC P2_r[] =
      {
        0x00, 0x11, 0x22, 0x33,
        0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xaa, 0xbb,
        0xcc, 0xee, 0xff, 0x0a
      };

      for (UC k = 0; k < 0x10; ++k)
        P2[k] = P2_r[0xf - k];
    }

    imito_step(P2);

    UC OB[] =
    {
      0x1a, 0xc9, 0xd9, 0x76,
      0xf8, 0x36, 0x36, 0xf5,
      0x5a, 0xe9, 0xef, 0x30,
      0x5e, 0x7c, 0x90, 0xd2
    };

    for (UC k = 0; k < 0x10; ++k)
      if (block_to_xor[k] != OB[0xf - k])
        return false;
  }

  //P3
  {
    UC P3[0x10];

    {
      UC P3_r[] =
      {
        0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x88,
        0x99, 0xaa, 0xbb, 0xcc,
        0xee, 0xff, 0x0a, 0x00
      };

      for (UC k = 0; k < 0x10; ++k)
        P3[k] = P3_r[0xf - k];
    }

    imito_step(P3);

    UC OB[] =
    {
      0x15, 0x64, 0x5a, 0xf4,
      0xa7, 0x8e, 0x50, 0xa9,
      0xab, 0xe8, 0xdb, 0x4b,
      0x75, 0x4d, 0xe3, 0xf2
    };

    for (UC k = 0; k < 0x10; ++k)
      if (block_to_xor[k] != OB[0xf - k])
        return false;
  }

  //P4
  {
    UC P4[0x10];

    {
      UC P4_r[] =
      {
        0x22, 0x33, 0x44, 0x55,
        0x66, 0x77, 0x88, 0x99,
        0xaa, 0xbb, 0xcc, 0xee,
        0xff, 0x0a, 0x00, 0x11
      };

      for (UC k = 0; k < 0x10; ++k)
        P4[k] = P4_r[0xf - k];
    }

    imito_final(P4);

    UC OB[] =
    {
      0x33, 0x6f, 0x4d, 0x29,
      0x60, 0x59, 0xfb, 0xe3,
      0x4d, 0xde, 0xb3, 0x5b,
      0x37, 0x74, 0x9c, 0x67
    };

    for (UC k = 0; k < 0x10; ++k)
      if (block_to_xor[k] != OB[0xf - k])
        return false;
  }

  return true;
}

bool Test_imito::test_P_not_full()
{
  for (UC k = 0; k < 0x10; ++k)
    block_to_xor[k] = 0;

  UC block[0x10] = { 0 };

  block[0x0] = 0x1;

  imito_final(block, 0x1); 

  UC block_cont[0x10] = { 0 };

  {
    block_cont[0xf] = 0x1;
    block_cont[0xe] = 0x80;

    UC key_cons[] =
    {
        0x52, 0xfb, 0x05, 0x78,
        0x9a, 0x73, 0xc7, 0x94,
        0x1b, 0xc0, 0xae, 0x65,
        0x30, 0x2a, 0x3b, 0x8e
    };

    for (UC k = 0; k < 0x10; ++k)
      block_cont[k] ^= key_cons[0xf - k];

    Give_ST(block_cont);

  }

  for (UC k = 0; k < 0x10; ++k)
    if (block[k] != block_cont[k])
      return false;

  return true;
}
