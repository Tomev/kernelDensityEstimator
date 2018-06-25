#include "linearKernel.h"

#include <cmath>


linearKernel::linearKernel() = default;

double linearKernel::getValue(double arg)
{
  /** Note, that it's a single dimension function. Doesn't do any checking (contract programming).
   *
   *  @brief Return value of linear kernel in arg.
   *
   *  @return Linear kernel value in arg.
   */

  if(fabs(arg) <= 1) return 0.5f;

  return 0.0f;
}

double linearKernel::getW()
{
  return 1.0 / 3.0;
}

double linearKernel::getU()
{
  return 0.5;
}

double linearKernel::getValue(std::vector<double> args)
{
  return i_singleArgumentFunction::getValue(args);
}


