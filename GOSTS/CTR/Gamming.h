#pragma once
/**
 * @file Gamming.h
 * @author Anatoliy Andreev (tolaywow@gmail.com)
 * @brief Реализация алгоритма работы блочного шифрования в режиме
 * гаммирования из ГОСТ 34.13.2015
 * @version 1.1
 * @date 2026-02-20
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <cstdint>
#include <stdexcept>
#include <vector>

/**
 * @brief
 *
 * @tparam CRYPTO Алгоритм блочного синхронного шифрования
 * @tparam n длина ключа в битах для алгоритма шифрования
 */
template <class CRYPTO, size_t n>
class Gamming : protected CRYPTO
{
public:
  Gamming(const uint16_t &s = n);
  virtual void push_IV(uint8_t *IV);
  virtual void push_key(uint8_t *key);
  virtual void Give_ST(uint8_t *block);
  virtual void Give_ST(uint8_t *block, const uint16_t &length_of_last_block);
  virtual ~Gamming();

protected:
  virtual void Add();
  virtual void Add(const uint8_t &num);
  virtual void T_r(uint8_t *block, uint8_t *CTR_after_encrypt, const uint16_t &r);

private:
  std::vector<uint8_t> Gamm;
  uint16_t s;
};

/**
 * @brief Construct a new Gamming< C R Y P T O, n>:: Gamming object
 *
 * @tparam CRYPTO Алгоритм блочного синхронного шифрования
 * @tparam n длина ключа в битах для алгоритма шифрования
 * @param s длина блока открытого текста, до которой обрезается шифргамма
 */
template <class CRYPTO, size_t n>
inline Gamming<CRYPTO, n>::Gamming(const uint16_t &s) : s(s)
{
  Gamm.resize(n / 0x8);
}

/**
 * @brief метод погружает в алгоритм синхропосылку
 *
 * @tparam CRYPTO Алгоритм блочного синхронного шифрования
 * @tparam n длина ключа в битах для алгоритма шифрования
 * @param IV указатель на C массив с синхропосылкой
 */
template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::push_IV(uint8_t *IV)
{
  if (IV == nullptr)
  {
    throw std::invalid_argument("IV");
  }

  for (uint8_t i = 0; i < n / 0x10; ++i)
  {
    Gamm[n / 0x10 + i] = IV[i];
  }
}

/**
 * @brief метод погружает в алгоритм ключ
 *
 * @tparam CRYPTO Алгоритм блочного синхронного шифрования
 * @tparam n длина ключа в битах для алгоритма шифрования
 * @param key указатель на C массив с ключом
 */
template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::push_key(uint8_t *key)
{
  if (key == nullptr)
  {
    throw std::invalid_argument("key");
  }

  CRYPTO::push_key(key);
}

/**
 * @brief получить шифртекст(шифртекст записывается в массив с открытым текстом)
 *
 * @tparam CRYPTO Алгоритм блочного синхронного шифрования
 * @tparam n длина ключа в битах для алгоритма шифрования
 * @param block указатель на блок открытого текста
 */
template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::Give_ST(uint8_t *block)
{
  if (block == nullptr)
  {
    throw std::invalid_argument("block");
  }
  Give_ST(block, s);
}

/**
 * @brief получить шифртекст для последнего блока
 * можно не использовать, если последний блок равен предыдущим
 * метод создан на случай, если выделено меньше памяти, чем на предыдущих блоках
 *
 * @tparam CRYPTO Алгоритм блочного синхронного шифрования
 * @tparam n длина ключа в битах для алгоритма шифрования
 * @param block
 * @param length_of_last_block
 */
template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::Give_ST(uint8_t *block, const uint16_t &length_of_last_block)
{
  if (block == nullptr)
  {
    throw std::invalid_argument("block");
  }
  if (length_of_last_block < 0x1)
  {
    throw std::invalid_argument("length_of_last_block");
  }

  uint8_t encrypt_block[n / 0x8] = {0};

  for (uint8_t i = 0; i < n / 0x8; i++)
  {
    encrypt_block[i] = Gamm[i];
  }

  CRYPTO::Give_ST(encrypt_block);

  T_r(block, encrypt_block, length_of_last_block);

  Add();
}

/**
 * @brief Destroy the Gamming< C R Y P T O, n>:: Gamming object
 *
 * @tparam CRYPTO Алгоритм блочного синхронного шифрования
 * @tparam n длина ключа в битах для алгоритма шифрования
 */
template <class CRYPTO, size_t n>
inline Gamming<CRYPTO, n>::~Gamming()
{
}

/**
 * @brief дополнение блока шифргаммы 1 по модулю n
 *
 * @tparam CRYPTO Алгоритм блочного синхронного шифрования
 * @tparam n длина ключа в битах для алгоритма шифрования
 */
template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::Add()
{
  Add(0);
}
/**
 * @brief дополнение блока шифргаммы 1 по модулю n
 * метод рекурсивный из-за неопределенной длины блока
 *
 * @tparam CRYPTO Алгоритм блочного синхронного шифрования
 * @tparam n длина ключа в битах для алгоритма шифрования
 * @param num
 */
template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::Add(const uint8_t &num)
{
  if (num < n / 0x8)
  {
    ++Gamm[num];
    if (Gamm[num] == 0)
    {
      Add(num + 0x1);
    }
  }
}
/**
 * @brief получения шифрблока
 *
 * @tparam CRYPTO Алгоритм блочного синхронного шифрования
 * @tparam n длина ключа в битах для алгоритма шифрования
 * @param block блок открытого текста
 * @param CTR_after_encrypt шифргамма после зашифрования
 * @param r количиство бит для обрезания
 */
template <class CRYPTO, size_t n>
inline void Gamming<CRYPTO, n>::T_r(uint8_t *block, uint8_t *CTR_after_encrypt, const uint16_t &r)
{
  for (uint8_t i = 0; i < r / 0x8 - 0x1; i++)
  {
    block[i] ^= CTR_after_encrypt[n / 0x8 - r / 0x8 + i];
  }
  if (r % 0x8 == 0)
  {
    block[r / 0x8 - 0x1] ^= CTR_after_encrypt[n / 0x8 - 0x1];
  }
  else
  {
    uint8_t x = 0x1, z = r % 0x8;

    while (z > 0x1)
    {
      x <<= 0x1;

      x ^= 0x1;

      --z;
    }

    block[r / 0x8 - 0x1] ^= (CTR_after_encrypt[n / 0x8 - 0x1] ^ x);
  }
}
