#include "Gamming.h"
#include "Imito.h"
#include "GwCLbCT.h"
#include "Grass_hopper.h"
#include <fstream>


#define UC unsigned char
#define qq >>std::noskipws>>
#define pp <<std::noskipws<<
#define TEST
#define ENCRYPT

int main()
{
#ifdef TEST
  //Gamming test
  {
    Gamming<Grass_hopper, 0x80> x(0x80);

    unsigned __int8 IV[0x8] = { 0xef, 0xac, 0x90, 0x78, 0x56, 0x34, 0x12 };

    UC text[0x10] = { 0 };

    //x.push_IV(IV);

    UC key[0x20] = { 0 };

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

      x.push_key(key);

      x.Give_ST(key);

    }

  }

  //Imito test
  {
    Imito<Grass_hopper, 0x80> x;

    UC key[0x20] = { 0 };

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

      x.push_key(key);


      //P1
      {
        UC P1[0x10] = { 0 };

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

        x.imito_step(P1);
      }
      //P2
      {
        UC P2[0x10] = { 0 };

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

        x.imito_step(P2);
      }

      //P3
      {
        UC P3[0x10] = { 0 };

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

        x.imito_step(P3);
      }

      //P4
      {
        UC P4[0x10] = { 0 };

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

        x.imito_final(P4);
        x.imito_final(P4);
      }
    }
  }

  //GwCLbCT
  {
    GwCLbCT<Grass_hopper, 0x80> x(0x20);

    {
      UC key[0x20] = { 0 };

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

      UC IV[0x20] = { 0 };

      UC IV_[0x20] =
      {
        0x12, 0x34, 0x56, 0x78,
        0x90, 0xab, 0xce, 0xf0,
        0xa1, 0xb2, 0xc3, 0xd4,
        0xe5, 0xf0, 0x01, 0x12,
        0x23, 0x34, 0x45, 0x56,
        0x67, 0x78, 0x89, 0x90,
        0x12, 0x13, 0x14, 0x15,
        0x16, 0x17, 0x18, 0x19
      };

      for (UC k = 0; k < 0x20; ++k)
        IV[k] = IV_[0x1f - k];


      x.push_IV_and_key(IV, key);

      //P1
      {
        UC P1[0x10] = { 0 };

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

        x.Give_ST(P1);
      }

      //P2
      {
        UC P2[0x10] = { 0 };

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

        x.Give_ST(P2);
      }

      //P3
      {
        UC P3[0x10] = { 0 };

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

        x.Give_ST(P3);
      }

      //P4
      {
        UC P4[0x10] = { 0 };

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

        x.Give_ST(P4);
      }
    }
  }

#endif 

#ifdef ENCRYPT
  {
    GwCLbCT<Grass_hopper, 0x80> x(0x20);
  
    Imito<Grass_hopper, 0x80> summ;

    std::ifstream KEY("key", std::ios_base::binary);
    std::ifstream TEXT("text", std::ios_base::binary);
    std::ifstream IV("IV", std::ios_base::binary);

    std::ofstream OUT("OUT", std::ios_base::binary);

    unsigned __int8 key[0x20] = { 0 }, iv[0x20] = {0};

    unsigned __int64 length_of_file = 0,loe=0;

    for (UC i = 0; i < 0x20; i++)
    {
      KEY qq key[i];
      IV qq iv[i];
    }
    
    x.push_IV_and_key(iv,key);
    summ.push_key(key);

    
    TEXT.seekg(0, std::ios::end);

    length_of_file = TEXT.tellg();

    TEXT.seekg(0);

    while (loe<length_of_file)
    {
      UC k = 0;
      UC block1[0x10] = {0};

      while (k < 0x10 && (TEXT qq block1[k]))
      {
        ++k;
        ++loe;
      }

      if (loe == length_of_file)
      {
        UC block_temp[0x10] = {0};
        for (UC i = 0; i < 0x10; i++)
        {
          block_temp[i] = block1[i];
        }
        
        x.Give_ST(block1, k);
        

        for (UC i = 0; i < k; i++)
        {
          OUT pp block1[i];
        }

        /*summ.imito_final(block_temp, k);

        for (UC i = 0; i <0x10; i++)
        {
          OUT << std::noskipws << block_temp[i];
        }*/

      }
      else
      {
        //summ.imito_step(block);
        x.Give_ST(block1);        

        for (UC i = 0; i < 0x10; i++)
        {
          OUT pp block1[i];
        }
      }

      k = 0;
    }
  }
#endif



  return 0;
}