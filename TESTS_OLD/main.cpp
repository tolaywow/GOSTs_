#include "Gamming.h"
#include "Imito.h"
#include "GwCLbCT.h"
#include "Grass_hopper.h"
#include "Magma.h"
#include "Hash512.h"
#include "H512_test.h"
/*
#include "GwOF_Test.h"
*/
#include "Gamming_with_output_feedback.h"
#include <fstream>

/**
 * Макрос заменяющий длинную запись(чтение) потока в(из) файл(а) без пропуска пустых символов
 */
#define qq >> std::noskipws >>
#define pp << std::noskipws <<

/**
 * подключение макросов для всех вариантов запуска проекта
 */
#define TEST
// #define ENCRYPT
// #define DECRYPT
// #define GENERATOR
// #define H512

/**
 * Проект с тестированием, зашифрованием, расшифрованием, хэшированием(512) и
 * генератором псевдослучайной последовательности.
 * Все варианты запускаются с помощью макросов
 */
int main()
{
#ifdef TEST
  // Gamming test
  {
    Gamming<Grass_hopper, 0x80> x(0x80);

    unsigned __int8 IV[0x8] = {0xef, 0xac, 0x90, 0x78, 0x56, 0x34, 0x12};

    uint8_t text[0x10] = {0};

    // x.push_IV(IV);

    uint8_t key[0x20] = {0};

    {
      uint8_t key_r[] =
          {
              0x88, 0x99, 0xaa, 0xbb,
              0xcc, 0xdd, 0xee, 0xff,
              0x00, 0x11, 0x22, 0x33,
              0x44, 0x55, 0x66, 0x77,
              0xfe, 0xdc, 0xba, 0x98,
              0x76, 0x54, 0x32, 0x10,
              0x01, 0x23, 0x45, 0x67,
              0x89, 0xab, 0xcd, 0xef};

      for (uint8_t k = 0; k < 0x20; ++k)
        key[k] = key_r[0x1f - k];

      x.push_key(key);

      x.Give_ST(key);
    }
  }

  // Imito test
  {
    Imito<Grass_hopper, 0x80> x;

    uint8_t key[0x20] = {0};

    {
      uint8_t key_r[] =
          {
              0x88, 0x99, 0xaa, 0xbb,
              0xcc, 0xdd, 0xee, 0xff,
              0x00, 0x11, 0x22, 0x33,
              0x44, 0x55, 0x66, 0x77,
              0xfe, 0xdc, 0xba, 0x98,
              0x76, 0x54, 0x32, 0x10,
              0x01, 0x23, 0x45, 0x67,
              0x89, 0xab, 0xcd, 0xef};

      for (uint8_t k = 0; k < 0x20; ++k)
        key[k] = key_r[0x1f - k];

      x.push_key(key);

      // P1
      {
        uint8_t P1[0x10] = {0};

        {
          uint8_t P1_r[] =
              {
                  0x11, 0x22, 0x33, 0x44,
                  0x55, 0x66, 0x77, 0x00,
                  0xff, 0xee, 0xdd, 0xcc,
                  0xbb, 0xaa, 0x99, 0x88};

          for (uint8_t k = 0; k < 0x10; ++k)
            P1[k] = P1_r[0xf - k];
        }

        x.imito_step(P1);
      }
      // P2
      {
        uint8_t P2[0x10] = {0};

        {
          uint8_t P2_r[] =
              {
                  0x00, 0x11, 0x22, 0x33,
                  0x44, 0x55, 0x66, 0x77,
                  0x88, 0x99, 0xaa, 0xbb,
                  0xcc, 0xee, 0xff, 0x0a};

          for (uint8_t k = 0; k < 0x10; ++k)
            P2[k] = P2_r[0xf - k];
        }

        x.imito_step(P2);
      }

      // P3
      {
        uint8_t P3[0x10] = {0};

        {
          uint8_t P3_r[] =
              {
                  0x11, 0x22, 0x33, 0x44,
                  0x55, 0x66, 0x77, 0x88,
                  0x99, 0xaa, 0xbb, 0xcc,
                  0xee, 0xff, 0x0a, 0x00};

          for (uint8_t k = 0; k < 0x10; ++k)
            P3[k] = P3_r[0xf - k];
        }

        x.imito_step(P3);
      }

      // P4
      {
        uint8_t P4[0x10] = {0};

        {
          uint8_t P4_r[] =
              {
                  0x22, 0x33, 0x44, 0x55,
                  0x66, 0x77, 0x88, 0x99,
                  0xaa, 0xbb, 0xcc, 0xee,
                  0xff, 0x0a, 0x00, 0x11};

          for (uint8_t k = 0; k < 0x10; ++k)
            P4[k] = P4_r[0xf - k];
        }

        x.imito_final(P4);
        x.imito_final(P4);
      }
    }
  }

  // GwCLbCT
  {
    GwCLbCT<Grass_hopper, 0x80> x(0x20);

    {
      uint8_t key[0x20] = {0};

      {
        uint8_t key_r[] =
            {
                0x88, 0x99, 0xaa, 0xbb,
                0xcc, 0xdd, 0xee, 0xff,
                0x00, 0x11, 0x22, 0x33,
                0x44, 0x55, 0x66, 0x77,
                0xfe, 0xdc, 0xba, 0x98,
                0x76, 0x54, 0x32, 0x10,
                0x01, 0x23, 0x45, 0x67,
                0x89, 0xab, 0xcd, 0xef};

        for (uint8_t k = 0; k < 0x20; ++k)
          key[k] = key_r[0x1f - k];
      }

      uint8_t IV[0x20] = {0};

      uint8_t IV_[0x20] =
          {
              0x12, 0x34, 0x56, 0x78,
              0x90, 0xab, 0xce, 0xf0,
              0xa1, 0xb2, 0xc3, 0xd4,
              0xe5, 0xf0, 0x01, 0x12,
              0x23, 0x34, 0x45, 0x56,
              0x67, 0x78, 0x89, 0x90,
              0x12, 0x13, 0x14, 0x15,
              0x16, 0x17, 0x18, 0x19};

      for (uint8_t k = 0; k < 0x20; ++k)
        IV[k] = IV_[0x1f - k];

      x.push_IV_and_key(IV, key);

      // P1
      {
        uint8_t P1[0x10] = {0};

        {
          uint8_t P1_r[] =
              {
                  0x11, 0x22, 0x33, 0x44,
                  0x55, 0x66, 0x77, 0x00,
                  0xff, 0xee, 0xdd, 0xcc,
                  0xbb, 0xaa, 0x99, 0x88};

          for (uint8_t k = 0; k < 0x10; ++k)
            P1[k] = P1_r[0xf - k];
        }

        x.Give_ST(P1);
      }

      // P2
      {
        uint8_t P2[0x10] = {0};

        {
          uint8_t P2_r[] =
              {
                  0x00, 0x11, 0x22, 0x33,
                  0x44, 0x55, 0x66, 0x77,
                  0x88, 0x99, 0xaa, 0xbb,
                  0xcc, 0xee, 0xff, 0x0a};

          for (uint8_t k = 0; k < 0x10; ++k)
            P2[k] = P2_r[0xf - k];
        }

        x.Give_ST(P2);
      }

      // P3
      {
        uint8_t P3[0x10] = {0};

        {
          uint8_t P3_r[] =
              {
                  0x11, 0x22, 0x33, 0x44,
                  0x55, 0x66, 0x77, 0x88,
                  0x99, 0xaa, 0xbb, 0xcc,
                  0xee, 0xff, 0x0a, 0x00};

          for (uint8_t k = 0; k < 0x10; ++k)
            P3[k] = P3_r[0xf - k];
        }

        x.Give_ST(P3);
      }

      // P4
      {
        uint8_t P4[0x10] = {0};

        {
          uint8_t P4_r[] =
              {
                  0x22, 0x33, 0x44, 0x55,
                  0x66, 0x77, 0x88, 0x99,
                  0xaa, 0xbb, 0xcc, 0xee,
                  0xff, 0x0a, 0x00, 0x11};

          for (uint8_t k = 0; k < 0x10; ++k)
            P4[k] = P4_r[0xf - k];
        }

        x.Give_ST(P4);
      }
    }
  }

  // GwOF
  {
    /* GwOF_Test x;

     x.result_of_testing();*/

    {
      Gamming_with_output_feedback<Grass_hopper, 128> z(128, 256);
      {

        uint8_t K_re[] = {
            0x88, 0x99, 0xaa, 0xbb,
            0xcc, 0xdd, 0xee, 0xff,
            0x00, 0x11, 0x22, 0x33,
            0x44, 0x55, 0x66, 0x77,
            0xfe, 0xdc, 0xba, 0x98,
            0x76, 0x54, 0x32, 0x10,
            0x01, 0x23, 0x45, 0x67,
            0x89, 0xab, 0xcd, 0xef};

        uint8_t IV_re[] = {
            0x12, 0x34, 0x56, 0x78,
            0x90, 0xab, 0xce, 0xf0,
            0xa1, 0xb2, 0xc3, 0xd4,
            0xe5, 0xf0, 0x01, 0x12,
            0x23, 0x34, 0x45, 0x56,
            0x67, 0x78, 0x89, 0x90,
            0x12, 0x13, 0x14, 0x15,
            0x16, 0x17, 0x18, 0x19};
        uint8_t IV[0x20], K[0x20];

        for (size_t i = 0; i < 0x32; i++)
        {
          IV[i] = IV_re[0x1f - i];
          K[i] = K_re[0x1f - i];
        }

        z.push_IV_and_key(IV, K);
      }

      // open text
      uint8_t P1_re[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88};
      uint8_t Р2_re[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xee, 0xff, 0x0a};
      uint8_t Р3_re[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xee, 0xff, 0x0a, 0x00};
      uint8_t Р4_re[] = {0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xee, 0xff, 0x0a, 0x00, 0x11};

      uint8_t P1[0x10], P2[0x10], P3[0x10], P4[0x10];

      for (size_t i = 0; i < 0x10; i++)
      {
        P1[i] = P1_re[0xf - i];
        P2[i] = Р2_re[0xf - i];
        P3[i] = Р3_re[0xf - i];
        P4[i] = Р4_re[0xf - i];
      }
      z.Give_ST(P1);
      z.Give_ST(P2);
      z.Give_ST(P3);
      z.Give_ST(P4);
    }
  }

#endif // TEST

#ifdef ENCRYPT
  {
    uint64_t pos = 0;

    {
      std::fstream POS("pos.txt");

      if (!(POS qq pos))

      {
        if (POS.is_open())
          POS pp 0x0;
        else
        {
          std::ofstream CF("pos.txt");
          CF pp 0x0;
        }
      }
    }

    std::ifstream KEY("key", std::ios_base::binary);

    std::ifstream IV("IV", std::ios_base::binary);

    unsigned __int8 key[0x20] = {0}, iv[0x20] = {0};

    unsigned __int64 length_of_file = 0, loe = 0;

    KEY.seekg(0x40 * pos);

    IV.seekg(0x20 * pos);

    for (uint8_t i = 0; i < 0x20; i++)
    {
      KEY qq key[i];
      IV qq iv[i];
    }

    GwCLbCT<Grass_hopper, 0x80> x(0x20);

    Imito<Grass_hopper, 0x80> summ;

    x.push_IV_and_key(iv, key);

    for (uint8_t i = 0; i < 0x20; i++)
      KEY qq key[i];

    summ.push_key(key);

    std::ifstream TEXT("file_in", std::ios_base::binary);

    TEXT.seekg(0, std::ios::end);

    length_of_file = TEXT.tellg();

    TEXT.seekg(0);

    std::ofstream OUT("file_out.txt", std::ios_base::binary);

    while (loe < length_of_file)
    {
      uint8_t k = 0;
      uint8_t block1[0x10] = {0};

      while (k < 0x10 && (TEXT qq block1[k]))
      {
        ++k;
        ++loe;
      }

      if (loe == length_of_file)
      {
        uint8_t block_temp[0x10] = {0};

        for (uint8_t i = 0; i < 0x10; i++)
        {
          block_temp[i] = block1[i];
        }

        x.Give_ST(block1, k);

        for (uint8_t i = 0; i < k; i++)
        {
          OUT pp block1[i];
        }

        summ.imito_final(block_temp, k);

        std::ofstream IM("imito.txt", std::ios_base::binary);

        for (uint8_t i = 0; i < 0x10; i++)
        {
          IM pp block_temp[i];
        }
      }
      else
      {
        summ.imito_step(block1);

        x.Give_ST(block1);

        for (uint8_t i = 0; i < 0x10; i++)
        {
          OUT pp block1[i];
        }
      }

      k = 0;
    }
  }

#endif // ENCRYPT

#ifdef DECRYPT
  {
    GwCLbCT<Grass_hopper, 0x80> x(0x20);

    Imito<Grass_hopper, 0x80> summ;

    uint64_t pos = 0;
    std::fstream POS("pos.txt");

    if (!(POS qq pos))
    {
      if (POS.is_open())
        POS pp 0x0;
      else
      {
        std::ofstream CF("pos.txt");
        CF pp 0x0;
      }
    }

    std::ifstream KEY("key", std::ios_base::binary);

    std::ifstream IV("IV", std::ios_base::binary);

    unsigned __int8 key[0x20] = {0}, iv[0x20] = {0};

    unsigned __int64 length_of_file = 0, loe = 0;

    KEY.seekg(0x40 * pos);

    IV.seekg(0x20 * pos);

    for (uint8_t i = 0; i < 0x20; i++)
    {
      KEY qq key[i];
      IV qq iv[i];
    }

    x.push_IV_and_key(iv, key);

    for (uint8_t i = 0; i < 0x20; i++)
    {
      KEY qq key[i];
    }

    summ.push_key(key);

    std::ifstream TEXT("file_out.txt", std::ios_base::binary);

    TEXT.seekg(0, std::ios::end);

    length_of_file = TEXT.tellg();

    TEXT.seekg(0);

    std::ofstream OUT("file_in", std::ios_base::binary);

    while (loe < length_of_file)
    {
      uint8_t k = 0;
      uint8_t block1[0x10] = {0};

      while (k < 0x10 && (TEXT qq block1[k]))
      {
        ++k;
        ++loe;
      }

      if (loe == length_of_file)
      {
        x.Give_OT(block1, k);

        for (uint8_t i = 0; i < k; i++)
          OUT pp block1[i];

        summ.imito_final(block1, k);

        std::ifstream IM("imito.txt", std::ios_base::binary);

        for (uint8_t i = 0; i < 0x10; i++)
        {
          uint8_t z = 0;

          IM qq z;
          if (z != block1[i])
          {

            OUT.close();
            OUT.open("file_in", std::ios_base::trunc);
            OUT.close();
            std::ofstream ERROR("отчет об ошибке.txt", std::ios::ate);
            ERROR pp "Имитовставка не совпала, расшифрованный файл очищен\n";
          }
        }
      }
      else
      {
        x.Give_OT(block1);

        summ.imito_step(block1);

        for (uint8_t i = 0; i < 0x10; i++)
        {
          OUT pp block1[i];
        }
      }

      k = 0;
    }
  }
#endif // DECRYPT

#ifdef GENERATOR
  {
    std::fstream POS("pos");

    uint64_t pos = 0;

    if (!(POS qq pos))
    {
      if (POS.is_open())
        POS pp 0x1;
      else
      {
        std::ofstream CF("pos");
        CF pp 0x1;
      }
    }
    else
    {
      POS.clear();
      POS pp pos + 0x1;
    }

    Gamming<Grass_hopper, 0x80> generate;

    // push key
    {
      std::ifstream KEY("key.in", std::ios_base::binary);

      KEY.seekg(0x20 * pos);

      uint8_t key[0x20] = {0};

      for (uint8_t i = 0; i < 0x20; i++)
        KEY qq key[i];

      generate.push_key(key);
    }

    // push IV
    {
      std::ifstream IV("iv.in", std::ios_base::binary);

      IV.seekg(0x8 * pos);

      uint8_t iv[0x8] = {0};

      for (uint8_t i = 0; i < 0x8; i++)
        IV qq iv[i];

      generate.push_IV(iv);
    }

    // generate
    {
      char name[0xff];

      _itoa_s(static_cast<__int32>(pos), name, 0xa);

      std::ofstream RES_KEYS(name, std::ios_base::binary);

      uint16_t k = 0x1;
      while (k != 0)
      {
        uint8_t res[0x10] = {0};

        generate.Give_ST(res);

        for (uint8_t i = 0; i < 0x10; ++i)
          RES_KEYS pp res[i];
        ++k;
      }
    }
  }

#endif // GENERATOR

#ifdef H512
  H512_test Test_H512;
  Test_H512.result_of_testing();
#endif // H512
  return 0;
}