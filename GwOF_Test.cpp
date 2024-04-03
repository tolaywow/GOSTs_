#include "GwOF_Test.h"

GwOF_Test::GwOF_Test()
{
}

bool GwOF_Test::result_of_testing()
{
  bool mass[0x1];

  if (result_of_testing(mass))
    return true;
  else
    return false;
}

bool GwOF_Test::result_of_testing(bool* mass)
{
  if (Test_of_vector())
  {
    mass[0] = true;
  }
  else
  {
    mass[0] = false;
    return false;
  }
  return true;
}

bool GwOF_Test::Test_of_vector()
{
  R.push_back(0x4);
  if (R[0]==0x4)
  {
    return true;
  }

  return false;
}
