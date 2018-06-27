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

/** Return value of triangular kernel in arg. Note, that it's a single dimension function.
   *  Doesn't do any checking (contract programming).
   *
   *  @brief Return value of triangular kernel in arg.
   *
   *  @param Single real value.
   *
   *  @return Triangular kernel value in arg.
   */
double triangularKernel::getValue(double arg)
{
  if(fabs(arg) < 1) return 1.0f - fabs(arg);

  return 0.0f;
}

double triangularKernel::getValue(std::vector<double> args)
{
  return i_singleArgumentFunction::getValue(args);
}


