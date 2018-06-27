#include <cmath>
#include "triangularKernel.h"

triangularKernel::triangularKernel() = default;

double triangularKernel::getW()
{
  return 2.0f / 3.0f;
}

double triangularKernel::getU()
{
  return 1.0f / 6.0f;
}

double triangularKernel::getValue(double arg)
{
  /** Return value of triangular kernel in arg. Note, that it's a single dimension function.
   *  Doesn't do any checking (contract programming).
   *
   *  @brief Return value of triangular kernel in arg.
   *
   *  @return Triangular kernel value in arg.
   */

  if(fabs(arg) < 1) return 1.0f - fabs(arg);

  return 0.0f;
}

double triangularKernel::getValue(std::vector<double> args)
{
  return i_singleArgumentFunction::getValue(args);
}


