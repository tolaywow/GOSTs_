#pragma once
#include "Hash512.h"
class H512_test :
    public Hash512
{
public:
  H512_test();
  virtual bool result_of_testing(bool* mass);
  virtual bool result_of_testing();
protected:
  virtual bool test_S();
  virtual bool test_P();
  virtual bool test_X();
  virtual bool test_l();
  virtual bool test_L();
  virtual bool test_Ki();

};

