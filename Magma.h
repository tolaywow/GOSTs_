#pragma once
class Magma
{
public:
  Magma();
  virtual ~Magma() {};

  virtual void push_key(const unsigned __int8* key_new);
  virtual void Give_ST(unsigned __int8* block);
  virtual void Give_OT(unsigned __int8* block);
  protected:
  virtual void g_k(unsigned __int8* text, const unsigned __int8* key);
  virtual void G_k(unsigned __int8* a0, unsigned __int8* a1, const unsigned __int8 num_of_key);
  virtual void Gs_k(unsigned __int8* a0, unsigned __int8* a1);
private:
  unsigned __int8 K[0x20];//Ki=K[0x4*(i-0x1)]
  Magma(const Magma&);
  Magma& operator=(const Magma&);
};

