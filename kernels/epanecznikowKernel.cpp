#include "epanecznikowKernel.h"

#include <cmath>

epanecznikowKernel::epanecznikowKernel() = default;

double epanecznikowKernel::getValue(std::vector<double> args)
{
  /** Note, that it's a single dimension function. It only works on first element of vector,
   *  and doesn't do any checking (contract programming).
   *
   *  @brief Return value of epanecznikow kernel in args[0].
   *
   *  @return Linear epanecznikow value in args[0].
   */

  return getValue(args[0]);
}

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
   *  @return Linear epanecznikow value in arg.
   */

  if(fabs(arg) <= 1) return 3.0/4.0 * (1 - pow(arg, 2));

  return 0.0f;
}


