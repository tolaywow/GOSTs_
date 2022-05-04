#pragma once
class Grass_hopper
{
public:
  Grass_hopper();
  ~Grass_hopper();
  virtual void push_key(const unsigned char* key_new);
  virtual void Give_ST(unsigned char* block);
  virtual void Give_OT(unsigned char* block);

protected:
  virtual void xors(const unsigned __int8* Key, unsigned __int8* block);
  virtual void S_p(unsigned char* block);
  virtual void S_l(unsigned char* block);
  virtual unsigned char l(const unsigned char* block);
  virtual void L_p(unsigned char* block);
  virtual void L_l(unsigned char* block);
  virtual  void key_new(unsigned char* key1, unsigned char* key2, const unsigned char numkey);
  virtual void Form_Key();

  unsigned char key[0x20], keys[0xa][0x10];


  Grass_hopper(const Grass_hopper&);
  virtual Grass_hopper& operator=(const Grass_hopper&) {};
};

