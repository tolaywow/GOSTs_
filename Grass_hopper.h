#pragma once
#include"abbreviation.h"

class Grass_hopper
{
  friend class GH_test;
public:
  Grass_hopper();
  virtual ~Grass_hopper();

  virtual void push_key(const UI8* key_new);
  virtual void Give_ST(UI8* block);
  virtual void Give_OT(UI8* block);

protected:
  virtual void xors(const UI8* Key, UI8* block);
  virtual void S_p(UI8* block);
  virtual void S_l(UI8* block);
  virtual UI8 l(const UI8* block);
  virtual void L_p(UI8* block);
  virtual void L_l(UI8* block);
  virtual  void key_new(UI8* key1, UI8* key2, const UI8 numkey);
  virtual void Form_Key();
  

private:
  UI8 key[0x20], keys[0xa][0x10];
  Grass_hopper(const Grass_hopper&);
  Grass_hopper& operator=(const Grass_hopper&);
};

