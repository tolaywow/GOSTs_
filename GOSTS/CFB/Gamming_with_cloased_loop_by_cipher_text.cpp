#include "Gamming_with_cloased_loop_by_cipher_text.h"
#include <stdexcept>

/**
 * @brief Construct a new Gw C Lb Ct:: Gw C Lb Ct object
 *
 * @param length_of_IV Размер выделяемой памяти для синхропосылки
 */
GwCLbCt::GwCLbCt(const uint16_t length_of_IV) : l_o_IV(length_of_IV),
                                                s(0x80)
{
  if (length_of_IV < 1)
  {
    throw std::invalid_argument("length_of_IV");
  }

  block_R.resize(length_of_IV);
}

/**
 * @brief Destroy the Gw C Lb Ct:: Gw C Lb Ct object
 *
 */
GwCLbCt::~GwCLbCt()
{
}
/**
 * @brief Загрузить синхропосылку
 *
 * @param IV Указатель на C-массив байт с синхропосылкой, не изменяется в методе
 */
void GwCLbCt::push_IV(const uint8_t *IV)
{
  if (IV == nullptr)
  {
    throw std::invalid_argument("IV");
  }

  for (uint8_t k = 0; k < l_o_IV; ++k)
  {
    block_R[k] = IV[k];
  }
}
/**
 * @brief Загрузить ключ и синхропосылку
 *
 * @param IV Указатель на C-массив байт с синхропосылкой, не изменяется в методе
 * @param key_new Указатель на C-массив байт с ключем, не изменяется в методе
 */
void GwCLbCt::push_IV_and_key(const uint8_t *IV, const uint8_t *key_new)
{
  if (key_new == nullptr)
  {
    throw std::invalid_argument("key_new");
  }
  else
  {
    if (IV == nullptr)
    {
      throw std::invalid_argument("IV");
    }
  }

  push_IV(IV);
  push_key(key_new);
}

/**
 * @brief Получить зашифрованный текст из открытого
 *
 * @param block Указатель на C-массив байт с блоком открытого текста, в него же записывается результат шифрования
 */
void GwCLbCt::Give_ST(uint8_t *block)
{
  if (block == nullptr)
  {
    throw std::invalid_argument("block");
  }

  uint8_t blockSR[0x10] = {0};

  for (uint8_t k = 0; k < 0x10; ++k)
  {
    blockSR[k] = block_R[l_o_IV - 0x10 + k];
  }

  Grass_hopper::Give_ST(blockSR);

  for (uint8_t k = 0; k < 0x10 && k < s / 0x8; ++k)
  {
    block[k] ^= blockSR[k];
  }

  for (uint8_t k = 0; k < l_o_IV - s / 0x8; ++k)
  {
    block_R[l_o_IV - 0x1 - k] = block_R[l_o_IV - k - 0x1 - s / 0x8];
  }

  for (uint8_t k = 0; k < s / 0x8; ++k)
  {
    block_R[k] = block[k];
  }
}

/**
 * @brief  Получить открытый текст из зашифрованного
 *
 * @param block Указатель на C-массив байт с блоком зашифрованного текста, в него же записывается результат расшифрования
 */
void GwCLbCt::Give_OT(uint8_t *block)
{
  if (block == nullptr)
  {
    throw std::invalid_argument("block");
  }

  uint8_t blockSR[0x10] = {0};

  for (uint8_t k = 0; k < 0x10; ++k)
    blockSR[k] = block_R[l_o_IV - 0x10 + k];

  Grass_hopper::Give_ST(blockSR);

  /*for (uint8_t k = 0; k < 0x10 && k < s / 0x10; ++k)
    block[k] ^= blockSR[k];*/

  for (uint8_t k = 0; k < l_o_IV - s / 0x8; ++k)
  {
    block_R[l_o_IV - 0x1 - k] = block_R[l_o_IV - k - 0x1 - s / 0x8];
  }

  for (uint8_t k = 0; k < s / 0x8; ++k)
  {
    block_R[k] = block[k];
  }

  for (uint8_t k = 0; k < 0x10 && k < s / 0x8; ++k)
  {
    block[k] ^= blockSR[k];
  }
}

/**
 * @brief Получить зашифрованный текст из открытого неполного блока
 *
 * @param block Указатель на C-массив байт с блоком открытого текста, в него же записывается результат шифрования
 * @param length_last_not_full_block длина неполного блока
 */
void GwCLbCt::Give_ST(uint8_t *block, const uint8_t length_last_not_full_block)
{
  if (block == nullptr)
  {
    throw std::invalid_argument("block");
  }

  if (length_last_not_full_block < 0x1)
  {
    throw std::invalid_argument("length_last_not_full_block");
  }

  uint8_t block_var[0x10] = {0};

  // for (uint8_t k = 0; k < length_last_not_full_block; ++k)
  //   block_var[k] = block[k];

  // block_var[length_last_not_full_block] = 0x80;

  Give_ST(block_var);

  for (uint8_t k = 0; k < length_last_not_full_block; ++k)
  {
    block[k] ^= block_var[k + 0x10 - length_last_not_full_block];
  }
}

/**
 * @brief  Получить открытый текст из зашифрованного неполного блока
 *
 * @param block Указатель на C-массив байт с блоком зашифрованного текста, в него же записывается результат расшифрования
 * @param length_last_not_full_block  длина неполного блока
 */
void GwCLbCt::Give_OT(uint8_t *block, const uint8_t length_last_not_full_block)
{
  if (block == nullptr)
  {
    throw std::invalid_argument("block");
  }

  if (length_last_not_full_block < 0x1)
  {
    throw std::invalid_argument("length_last_not_full_block");
  }

  uint8_t block_var[0x10] = {0};

  // for (uint8_t k = 0; k < length_last_not_full_block; ++k)
  //   block_var[k] = block[k];

  Give_OT(block_var);

  for (uint8_t k = 0; k < length_last_not_full_block; ++k)
  {
    block[k] ^= block_var[k + 0x10 - length_last_not_full_block];
  }
}

/**
 * @brief Установка размера обрезаемого блока шифргаммы
 *
 * @param s_in
 */
void GwCLbCt::push_s(const uint16_t s_in)
{

  if (s_in < 0x1)
  {
    throw std::invalid_argument("s_in");
  }
  s = s_in;
}
