#include "pluginBandwidthCalculator.h"

#include <cmath>

/** Sets rank of bandwidth counting method. Note, that only 2 and 3 are implemented due to lack of derivative
 *  counting methods and lack of necessity for higher ranks. If higher or lower rank would be passed, default rank
 *  (second) will be used.
 *
 *  @param newRank
 */
void pluginBandwidthCalculator::setRank(unsigned int newRank)
{
  if(newRank == THIRD_RANK)
    rank = THIRD_RANK;
  else
    rank = SECOND_RANK;
}

/** Returns bandwidth value calculated from given samples. Note that if samples are multidimensional it will return
 *  multidimensional bandwidth. Normal kernel was used.
 *
 *  @return Bandwidth value from given samples.
 */
std::vector<double> pluginBandwidthCalculator::getBandwidth(std::vector<std::vector<double>> samples)
{
  this->samples = samples;

  std::vector<double> bandwidth = std::vector<double>();

  for(unsigned int dimension = 0; dimension < samples[0].size(); ++dimension)
  {
    // Extract values at given dimension
    samplesValuesAtDimension.clear();

    for(std::vector<double> sample : samples)
      samplesValuesAtDimension.emplace_back(sample[dimension]);

    bandwidth.emplace_back(getRankedBandwidthAtGivenDimension());
  }

  return bandwidth;
}

/** Counts one dimensional bandwidth from given one dimensional samples.
 *
 *  @return One dimensional bandwidth.
 */
double pluginBandwidthCalculator::getRankedBandwidthAtGivenDimension()
{
  double h = -1.0;

  if(rank == THIRD_RANK)
    h = count3rdRankH();

  h = count2ndRankH(h);
  h = count1stRankH(h);

  h = kernel.getW() / countCapitalC(4, h);

  return pow(h / samplesValuesAtDimension.size(), 0.2);
}

double pluginBandwidthCalculator::count3rdRankH()
{
  double h = -2 * countKernels8thDerivativeValueAtPoint(0);
  h /= countSmallC(10);
  h /= samplesValuesAtDimension.size();

  int sigH = h < 0 ? -1 : 1;

  h = pow(fabs(h), 1.0/11.0);
  h *= sigH;

  return h;
}

double pluginBandwidthCalculator::count2ndRankH(double currentH)
{
  double denominator = 0.0;

  if(currentH < 0)
    denominator = countSmallC(8);
  else
    denominator = countCapitalC(8, currentH);

  double h = - 2.0 * countKernels6thDerivativeValueAtPoint(0);
  h /= samplesValuesAtDimension.size() * denominator;

  return pow(h, 1.0/9.0);
}

double pluginBandwidthCalculator::count1stRankH(double currentH)
{
  double h = - 2.0 * countKernels4thDerivativeValueAtPoint(0);
  h /= samplesValuesAtDimension.size();
  h /= countCapitalC(6, currentH);
  return pow(h, 1.0/7.0);
}

double pluginBandwidthCalculator::countSmallC(unsigned int xi)
{
  double c = countFactorial(xi);
  c /= countFactorial(xi / 2);
  c /= sqrt(M_PI);
  c /= pow(2 * countStandardDeviationEstimator(), xi + 1);
  return c;
}

double pluginBandwidthCalculator::countStandardDeviationEstimator()
{
  double E = countExpectedValueEstimator();
  double V = countVariationEstimator(E);
  return sqrt(V);
}

double pluginBandwidthCalculator::countExpectedValueEstimator()
{
  double E = 0.0;

  for(double value : samplesValuesAtDimension)
    E += value;

  E /= samplesValuesAtDimension.size();

  return E;
}

double pluginBandwidthCalculator::countVariationEstimator(double expectedValueEstimator)
{
  double variationEstimator = 0.0;

  for(double value : samplesValuesAtDimension)
    variationEstimator += pow(value - expectedValueEstimator, 2);

  variationEstimator /= samplesValuesAtDimension.size() - 1;

  return variationEstimator;
}

double pluginBandwidthCalculator::countFactorial(unsigned int number)
{
  unsigned  int factorial = 1;

  for(int i = 2; i <= number; ++i) factorial *= i;

  return factorial;
}

double pluginBandwidthCalculator::countCapitalC(unsigned int xi, double h)
{
  double (pluginBandwidthCalculator::*kernelXithDerivativePtr)(double);

  switch(xi)
  {
    case 8:
      kernelXithDerivativePtr = &pluginBandwidthCalculator::countKernels8thDerivativeValueAtPoint;
      break;
    case 6:
      kernelXithDerivativePtr = &pluginBandwidthCalculator::countKernels6thDerivativeValueAtPoint;
      break;
    case 4:
    default:
      kernelXithDerivativePtr = &pluginBandwidthCalculator::countKernels4thDerivativeValueAtPoint;
  }

  double C = 0.0;

  for(double iValue : samplesValuesAtDimension)
  {
    for(double jValue : samplesValuesAtDimension)
      C += (*this.*kernelXithDerivativePtr)((iValue - jValue) / h);
  }

  C /= ( pow(samplesValuesAtDimension.size(), 2) * pow(h, xi + 1) );

  return C;
}

double pluginBandwidthCalculator::countKernels8thDerivativeValueAtPoint(double x)
{
  return (pow(x, 8) - 28 * pow(x, 6) + 210 * pow(x, 4) - 420 * pow(x, 2) + 105) * exp(- 0.5 * pow(x, 2)) / sqrt(2 * M_PI);
}

double pluginBandwidthCalculator::countKernels6thDerivativeValueAtPoint(double x)
{
  return (pow(x, 6) - 15 * pow(x, 4) + 45 * pow(x, 2) - 15) * exp(-0.5 * pow(x, 2)) / sqrt(2 * M_PI);
}

double pluginBandwidthCalculator::countKernels4thDerivativeValueAtPoint(double x)
{
  return (pow(x, 4) - 6 * pow(x, 2) + 3) * exp(- 0.5 * pow(x, 2)) / sqrt(2 * M_PI);
}

