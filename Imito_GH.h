#pragma once
#include "Grass_hopper.h"

class Imito_GH : public Grass_hopper
{
  friend class Test_imito;

public:
  Imito_GH();

  virtual void imito_step(const uint8_t *block);
  virtual void imito_final(uint8_t *block, const uint8_t length_of_block_in_byte);
  virtual void imito_final(uint8_t *block);
  virtual void push_key(const uint8_t *key_new);

private:
  uint8_t block_to_xor[0x10];
  uint8_t key_imito[0x20];

protected:
  virtual bool MSB(const uint8_t *block);
};
