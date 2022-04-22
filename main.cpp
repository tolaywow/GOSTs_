#include "GH_test.h"
#include "Grass_hopper.h"
#include <iostream>

#include "Imito_GH.h"

#define UC unsigned char

int main()
{
  {
    GH_test x;
    std::cout << x.result_of_testing() << std::endl;
  }

  Imito_GH x;


  unsigned char key[0x20];

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
    {
      key[k] = key_r[0x1f - k];

    }

  }

  x.push_key(key);

  return 0;
}
