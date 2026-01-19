#pragma once
#include <stdint.h>

class Grass_hopper
{
  friend class GH_test;

public:
  Grass_hopper();
  virtual ~Grass_hopper();

  virtual void push_key(const uint8_t *key_new);
  virtual void Give_ST(uint8_t *block);
  virtual void Give_OT(uint8_t *block);

protected:
  virtual void xors(const uint8_t *Key, uint8_t *block);
  virtual void S_p(uint8_t *block);
  virtual void S_l(uint8_t *block);
  virtual uint8_t l(const uint8_t *block);
  virtual void L_p(uint8_t *block);
  virtual void L_l(uint8_t *block);
  virtual void key_new(uint8_t *key1, uint8_t *key2, const uint8_t numkey);
  virtual void Form_Key();

private:
  uint8_t key[0x20], keys[0xa][0x10];
  Grass_hopper(const Grass_hopper &);
  Grass_hopper &operator=(const Grass_hopper &);
};
