#pragma once
#include "Grass_hopper.h"
class GH_test :
  public Grass_hopper
{
public:
  GH_test();
  virtual bool result_of_testing(bool* mass);
  virtual bool result_of_testing();
protected:
  virtual bool test_S();
  virtual bool test_L();
  virtual bool test_X();
  virtual bool test_LX();
  virtual bool test_S_l();
  virtual bool test_SLX();
  virtual bool test_keys();
  virtual bool test_cry();
  virtual bool test_not_cry();
  /*  
  bool test_();
  bool test_();
  bool test_();*/
};