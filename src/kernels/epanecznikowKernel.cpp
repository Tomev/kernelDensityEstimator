#include "epanecznikowKernel.h"

#include <cmath>

epanecznikowKernel::epanecznikowKernel() = default;

double epanecznikowKernel::getW()
{
  return 0.2f;
}

double epanecznikowKernel::getU()
{
  return 0.6f;
}

double epanecznikowKernel::getValue(double arg)
{
  /** Note, that it's a single dimension function. Doesn't do any checking (contract programming).
   *
   *  @brief Return value of epanecznikow kernel in arg.
   *
   *  @return Epanecznikow kernel value in arg.
   */

  if(fabs(arg) <= 1) return 3.0/4.0 * (1 - pow(arg, 2));

  return 0.0f;
}

double epanecznikowKernel::getValue(std::vector<double> args)
{
  return i_singleArgumentFunction::getValue(args);
}


