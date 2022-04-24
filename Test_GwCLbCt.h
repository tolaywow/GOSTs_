#pragma once
#include "Gamming_with_cloased_loop_by_cipher_text.h"

class Test_GwCLbCt :
    public Gamming_with_cloased_loop_by_cipher_text
{
public:
  Test_GwCLbCt();

  virtual bool result_of_testing(bool* mass);
  virtual bool result_of_testing();
protected:
  virtual bool test_C();
  virtual bool test_P();
  /*
  
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();
  virtual bool test_();*/
};

