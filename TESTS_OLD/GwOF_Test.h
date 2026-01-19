#pragma once
#include "Grass_hopper.h"
#include <cstdint>
#include "Gamming_with_output_feedback.h"
class GwOF_Test : protected Gamming_with_output_feedback<Grass_hopper, 0x80>
{
public:
  GwOF_Test();
  virtual bool result_of_testing();
  virtual bool result_of_testing(bool *mass);

private:
  virtual bool Test_of_vector();
};
