#include "normalKernel.h"
#include <cmath>


normalKernel::normalKernel() = default;

normalKernel::normalKernel(double stdDev) : stdDev(stdDev){}

double normalKernel::getValue(double arg)
{
  /** Note, that it's a single dimension function. Doesn't do any checking (contract programming).
   *
   *  @brief Return value of N(0,stdDev) in arg.
   *
   *  @return Normal distribution probability density value in arg.
   */

  double result = exp(-pow((arg - 0), 2)) / (2 * pow(stdDev, 2));
  return result / (stdDev * sqrt(2 * M_PI));
}


double normalKernel::getValue(std::vector<double> args)
{
  /** Note, that it's a single dimension function. It only works on first element of vector,
   *  and doesn't do any checking (contract programming).
   *
   *  @brief Return value of N(0,stdDev) in args[0].
   *
   *  @return Normal distribution probability density value in args[0].
   */

  return getValue(args[0]);
}

double normalKernel::getW()
{
  return 1.0 / (2.0 * M_PI);
}

double normalKernel::getU()
{
  return 1.0;
}




