#pragma once
#include "Imito_GH.h"
class Test_imito :
    public Imito_GH
{
public:
  virtual bool result_of_testing(bool* mass);
  virtual bool result_of_testing();
protected:
  virtual bool test_R();
  virtual bool test_MSBR();
  virtual bool test_K1();
  virtual bool test_MSBK1();/*
  virtual bool test_K2();*/
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
  virtual bool test_();
  virtual bool test_();*/
};

