#include "GH_test.h"
#include "Grass_hopper.h"
#include "Test_imito.h"
#include "Imito_GH.h"
#include "Gamming_with_cloased_loop_by_cipher_text.h"

#include <iostream>

#include "Imito_GH.h"

#define UC unsigned char

int main()
{
  {
    GH_test x;
    std::cout << x.result_of_testing() << std::endl;
  }

  {
    Test_imito x;

    std::cout << x.result_of_testing() << std::endl;
  }
  
  {
    UC key[0x20] = { 0 }, IV[0x40] = { 0 }, block[0x10] = { 0 };

    IV[0] = 0x1;

    block[0x1] = 0x1;

    Gamming_with_cloased_loop_by_cipher_text x(0x40);

    x.push_s(0xff);

    x.push_IV_and_key(IV, key);

    x.Give_ST(block);

    x.push_IV(IV);

    x.Give_OT(block);
  }

  return 0;
}
