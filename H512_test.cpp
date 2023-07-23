#include "H512_test.h"

H512_test::H512_test()
{
}

bool H512_test::result_of_testing(bool* mass)
{
  bool result = true;

  if (!test_X())
  {
    result = false;
    mass[0] = result;
  }
  if (!test_S())
  {
    result = false;
    mass[0x1] = result;
  }
  if (!test_P())
  {
    result = false;
    mass[0x2] = result;
  }
  if (!test_l())
  {
    result = false;
    mass[0x3] = result;
  }
  if (!test_L())
  {
    result = false;
    mass[0x4] = result;
  }
  if (!test_Ki())
  {
    result = false;
    mass[0x5] = result;
  }
  if (!test_N())
  {
    result = false;
    mass[0x6] = result;
  }
  if (!test_hash())
  {
    result = false;
    mass[0x7] = result;
  }

    return result;
}

bool H512_test::result_of_testing()
{
  bool mass[0x10];
  return result_of_testing(mass);
}

bool H512_test::test_S()
{
  UI8 block[] = {
   0x22, 0xf7, 0xdf, 0x70, 0x89, 0x43, 0x68, 0x23,
   0x16, 0xf1, 0xdd, 0x72, 0x81, 0x4b, 0x66, 0x2d,
   0x14, 0xf3, 0xdb, 0x74, 0x83, 0x49, 0x6e, 0x25,
   0x1a, 0xfd, 0xd9, 0x76, 0x85, 0x4f, 0x6c, 0x27,
   0x12, 0xf5, 0xd7, 0x78, 0x87, 0x4d, 0x6a, 0x21,
   0x10, 0xf7, 0xdf, 0x70, 0x89, 0x43, 0x68, 0x23,
   0x16, 0xf1, 0xdd, 0x72, 0x81, 0x4b, 0x66, 0x2d,
   0x14, 0xf3, 0xdb, 0x74, 0x83, 0x49, 0x6e, 0x25
  };

  UI8 S_res[] = {
    0x65, 0xc0, 0x61, 0x32, 0x79, 0x51, 0xf3, 0x5a,
    0x99, 0xa6, 0xd8, 0x19, 0xf5, 0xa2, 0x9a, 0x01,
    0x93, 0xd2, 0x90, 0xff, 0xa9, 0x2a, 0xb2, 0x5c,
    0xf1, 0x4b, 0x53, 0x8a, 0xa8, 0xcc, 0x9d, 0x21,
    0xf0, 0xf4, 0xfe, 0x6d, 0xc9, 0x3a, 0x78, 0x18,
    0xe9, 0xc0, 0x61, 0x32, 0x79, 0x51, 0xf3, 0x5a,
    0x99, 0xa6, 0xd8, 0x19, 0xf5, 0xa2, 0x9a, 0x01,
    0x93, 0xd2, 0x90, 0xff, 0xa9, 0x2a, 0xb2, 0x5c
  };
  
  Hash512::S(block);

  for (size_t i = 0; i < 0x40; i++)
  {
    if (block[i] != S_res[i])
      return false;
  }

  return true;
}

bool H512_test::test_P()
{
  UI8 block[] = {
    0x65, 0xc0, 0x61, 0x32, 0x79, 0x51, 0xf3, 0x5a,
    0x99, 0xa6, 0xd8, 0x19, 0xf5, 0xa2, 0x9a, 0x01,
    0x93, 0xd2, 0x90, 0xff, 0xa9, 0x2a, 0xb2, 0x5c,
    0xf1, 0x4b, 0x53, 0x8a, 0xa8, 0xcc, 0x9d, 0x21,
    0xf0, 0xf4, 0xfe, 0x6d, 0xc9, 0x3a, 0x78, 0x18,
    0xe9, 0xc0, 0x61, 0x32, 0x79, 0x51, 0xf3, 0x5a,
    0x99, 0xa6, 0xd8, 0x19, 0xf5, 0xa2, 0x9a, 0x01,
    0x93, 0xd2, 0x90, 0xff, 0xa9, 0x2a, 0xb2, 0x5c
  };

  UI8 P_top[] = {
    0x65, 0x99, 0x93, 0xf1, 0xf0, 0xe9, 0x99, 0x93,
    0xc0, 0xa6, 0xd2, 0x4b, 0xf4, 0xc0, 0xa6, 0xd2,
    0x61, 0xd8, 0x90, 0x53, 0xfe, 0x61, 0xd8, 0x90,
    0x32, 0x19, 0xff, 0x8a, 0x6d, 0x32, 0x19, 0xff,
    0x79, 0xf5, 0xa9, 0xa8, 0xc9, 0x79, 0xf5, 0xa9,
    0x51, 0xa2, 0x2a, 0xcc, 0x3a, 0x51, 0xa2, 0x2a,
    0xf3, 0x9a, 0xb2, 0x9d, 0x78, 0xf3, 0x9a, 0xb2,
    0x5a, 0x01, 0x5c, 0x21, 0x18, 0x5a, 0x01, 0x5c
  };

    Hash512::P(block);

    for (size_t i = 0; i < 0x40; i++)
    {
      if (block[i] != P_top[i])
        return false;
    }

  return true;
}

bool H512_test::test_X()
{
  UI8 m[] = {
    0x01, 0x32, 0x31, 0x30, 0x39, 0x38, 0x37, 0x36,
    0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x39, 0x38,
    0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30,
    0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32,
    0x31, 0x30, 0x39, 0x38, 0x37, 0x36, 0x35, 0x34,
    0x33, 0x32, 0x31, 0x30, 0x39, 0x38, 0x37, 0x36,
    0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x39, 0x38,
    0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30 
  };

  UI8 key[] = {
    0x23, 0xc5, 0xee, 0x40, 0xb0, 0x7b, 0x5f, 0x15,
    0x23, 0xc5, 0xee, 0x40, 0xb0, 0x7b, 0x5f, 0x15,
    0x23, 0xc5, 0xee, 0x40, 0xb0, 0x7b, 0x5f, 0x15,
    0x23, 0xc5, 0xee, 0x40, 0xb0, 0x7b, 0x5f, 0x15,
    0x23, 0xc5, 0xee, 0x40, 0xb0, 0x7b, 0x5f, 0x15,
    0x23, 0xc5, 0xee, 0x40, 0xb0, 0x7b, 0x5f, 0x15,
    0x23, 0xc5, 0xee, 0x40, 0xb0, 0x7b, 0x5f, 0x15,
    0x23, 0xc5, 0xee, 0x40, 0xb0, 0x7b, 0x5f, 0x15
  };

  UI8 block[] = {
    0x22, 0xf7, 0xdf, 0x70, 0x89, 0x43, 0x68, 0x23,
    0x16, 0xf1, 0xdd, 0x72, 0x81, 0x4b, 0x66, 0x2d,
    0x14, 0xf3, 0xdb, 0x74, 0x83, 0x49, 0x6e, 0x25,
    0x1a, 0xfd, 0xd9, 0x76, 0x85, 0x4f, 0x6c, 0x27,
    0x12, 0xf5, 0xd7, 0x78, 0x87, 0x4d, 0x6a, 0x21,
    0x10, 0xf7, 0xdf, 0x70, 0x89, 0x43, 0x68, 0x23,
    0x16, 0xf1, 0xdd, 0x72, 0x81, 0x4b, 0x66, 0x2d,
    0x14, 0xf3, 0xdb, 0x74, 0x83, 0x49, 0x6e, 0x25
  };

  Hash512::xors(key, m);

  for (size_t i = 0; i < 0x40; i++)
  {
    if (m[i] != block[i])
      return false;
  }
  return true;
}

bool H512_test::test_l()
{
  UI64 C = 0;
  UI64 Res = 0xab8eff9ec7466498;

  Hash512::l(&C);

  if (C)
    return false;

  C -= 0x1;

  Hash512::l(&C);

  if (C != Res)
    return false;

  C = 0x3;
  
  Res = 0xac2453dd7d8f3d98;

  Hash512::l(&C);

  if (C != Res)
    return false;

  C = 0x5;

  Res = 0xe96cf57a878c47b5;

  Hash512::l(&C);

  if (C != Res)
    return false;


  return true;
}

bool H512_test::test_L()
{
  //simple test
  {
    UI8 var_block[0x40] = {0};

    UI8 var_result[] = {
      0xb3, 0x83, 0xfc, 0x2e, 0xce, 0xd4, 0xa5, 0x74,
      0xb3, 0x83, 0xfc, 0x2e, 0xce, 0xd4, 0xa5, 0x74,
      0xb3, 0x83, 0xfc, 0x2e, 0xce, 0xd4, 0xa5, 0x74,
      0xb3, 0x83, 0xfc, 0x2e, 0xce, 0xd4, 0xa5, 0x74,
      0xb3, 0x83, 0xfc, 0x2e, 0xce, 0xd4, 0xa5, 0x74,
      0xb3, 0x83, 0xfc, 0x2e, 0xce, 0xd4, 0xa5, 0x74,
      0xb3, 0x83, 0xfc, 0x2e, 0xce, 0xd4, 0xa5, 0x74,
      0xb3, 0x83, 0xfc, 0x2e, 0xce, 0xd4, 0xa5, 0x74
    };

    for (size_t i = 0; i < 0x40; i++)
    {
      var_block[i] = 0xfc;
    }

    Hash512::L(var_block);

    for (size_t i = 0; i < 0x40; i++)
    {
      if (var_block[i] != var_result[0x3f - i])
        return false;
    }
    
  }

  //real data test
  {

    UI8 block[] = {
      0x46, 0x43, 0x3e, 0xd6, 0x24, 0xdf, 0x43, 0x3e,
      0x45, 0x2f, 0x5e, 0x7d, 0x92, 0x45, 0x2f, 0x5e,
      0xd9, 0x89, 0x37, 0xe4, 0xac, 0xd9, 0x89, 0x37,
      0x5f, 0x14, 0xf1, 0x17, 0x99, 0x5f, 0x14, 0xf1,
      0xC0, 0xb6, 0x4b, 0xc2, 0x66, 0xc0, 0xb6, 0x4b,
      0xbe, 0x2d, 0x09, 0x20, 0x67, 0xbe, 0x2d, 0x09,
      0xec, 0x4e, 0x7a, 0xb0, 0xe0, 0xec, 0x4e, 0x7a,
      0x2c, 0xfd, 0xea, 0x48, 0xeb, 0x2c, 0xfd, 0xea
    };

    UI8 result[] = {
      0xe6, 0x00, 0x59, 0xd4, 0xd8, 0xe0, 0x75, 0x80,
      0x24, 0xc7, 0x3f, 0x6f, 0x31, 0x83, 0x65, 0x3f,
      0x56, 0x57, 0x91, 0x89, 0x60, 0x2a, 0xe4, 0xc2,
      0x1e, 0x79, 0x53, 0xeb, 0xc0, 0xe2, 0x12, 0xa0,
      0xCe, 0x78, 0xa8, 0xdf, 0x47, 0x5c, 0x2f, 0xd4,
      0xfc, 0x43, 0xfc, 0x4b, 0x71, 0xc0, 0x1e, 0x35,
      0xbe, 0x46, 0x5f, 0xb2, 0x0d, 0xad, 0x2c, 0xf6,
      0x90, 0xcd, 0xf6, 0x50, 0x28, 0x12, 0x1b, 0xb9
    };
    UI8 block_reverse[0x40] = {0};

    for (size_t i = 0; i < 0x40; i++)
    {
      block_reverse[i] = block[0x3f - i];
    }

    Hash512::L(block_reverse);

    for (size_t i = 0; i < 0x40; i++)
    {
      if (block_reverse[i] != result[0x3f - i])
        return false;
    }
  }

  return true;
}

bool H512_test::test_Ki()
{
  UI8 Key_rev[] = {
    0x0f, 0x79, 0x10, 0x40, 0x26, 0xb9, 0x00, 0xd8,
    0xd7, 0x68, 0xb6, 0xe2, 0x23, 0x48, 0x4c, 0x97,
    0x61, 0xe3, 0xc5, 0x85, 0xb3, 0xa4, 0x05, 0xa6,
    0xd2, 0xd8, 0x56, 0x5a, 0xda, 0x92, 0x6c, 0x3f,
    0x77, 0x82, 0xef, 0x12, 0x7c, 0xd6, 0xb9, 0x82,
    0x90, 0xbf, 0x61, 0x25, 0x58, 0xb4, 0xb6, 0x0a,
    0xa3, 0xcb, 0xc2, 0x8f, 0xd9, 0x4f, 0x95, 0x46,
    0x0d, 0x76, 0xb6, 0x21, 0xcb, 0x45, 0xbe, 0x70
  };
  
  UI8 Key[0x40] = { 0 };

  Hash512::Key_create(Key);

  for (size_t i = 0; i < 0x40; i++)
  {
    if (Hash512::Keys[0xc][i] != Key_rev[0x3f - i])
      return false;
  }

  return true;
}

bool H512_test::test_N()
{
  UI8 var = 0x2;

  Hash512::N_();

  if (N[0x1] != var)
    return false;

    return true;
}

bool H512_test::test_hash()
{
  UI8* res;
  //test length 504
  {

    UI8 text[] = {
      0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
      0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
      0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33,
      0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31,
      0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
      0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
      0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
      0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32,
    };

    UI8 res_orig[] =
    {
      0x48, 0x6f, 0x64, 0xc1, 0x91, 0x78, 0x79, 0x41,
      0x7f, 0xef, 0x08, 0x2b, 0x33, 0x81, 0xa4, 0xe2,
      0x11, 0xc3, 0x24, 0xf0, 0x74, 0x65, 0x4c, 0x38,
      0x82, 0x3a, 0x7b, 0x76, 0xf8, 0x30, 0xad, 0x00,
      0xfa, 0x1f, 0xba, 0xe4, 0x2b, 0x12, 0x85, 0xc0,
      0x35, 0x2f, 0x22, 0x75, 0x24, 0xbc, 0x9a, 0xb1,
      0x62, 0x54, 0x28, 0x8d, 0xd6, 0x86, 0x3d, 0xcc,
      0xd5, 0xb9, 0xf5, 0x4a, 0x1a, 0xd0, 0x54, 0x1b
    };

    Hash512::N[0x1] = 0;

    res = Hash512::give_hash(text, 504);

    for (size_t i = 0; i < 0x40; i++)
    {
      if (res[i] != res_orig[0x3f - i])
        return false;
    }
  }

  //test length 
  {
    for (size_t i = 0; i < 0x40; i++)
    {
      Hash512::h[i] = 0;
      Hash512::N[i] = 0;
      Hash512::Summ[i] = 0;
    }

    UI8 text[0x48] =
    {
      0xd1, 0xe5, 0x20, 0xe2, 0xe5, 0xf2, 0xf0, 0xe8,
      0x2c, 0x20, 0xd1, 0xf2, 0xf0, 0xe8, 0xe1, 0xee,
      0xe6, 0xe8, 0x20, 0xe2, 0xed, 0xf3, 0xf6, 0xe8,
      0x2c, 0x20, 0xe2, 0xe5, 0xfe, 0xf2, 0xfa, 0x20,
      0xf1, 0x20, 0xec, 0xee, 0xf0, 0xff, 0x20, 0xf1,
      0xf2, 0xf0, 0xe5, 0xeb, 0xe0, 0xec, 0xe8, 0x20,
      0xed, 0xe0, 0x20, 0xf5, 0xf0, 0xe0, 0xe1, 0xf0,
      0xfb, 0xff, 0x20, 0xef, 0xeb, 0xfa, 0xea, 0xfb,
      0x20, 0xc8, 0xe3, 0xee, 0xf0, 0xe5, 0xe2, 0xfb
    };

    res = Hash512::give_hash(text, 0x240);

  }
  
  return true;
}


