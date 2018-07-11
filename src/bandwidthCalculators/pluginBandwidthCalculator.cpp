#include "pluginBandwidthCalculator.h"

#include <cmath>

void pluginBandwidthCalculator::setRank(unsigned int newRank)
{
  if(newRank == THIRD_RANK)
    rank = 3;
  else
    rank = 2;
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

  for(int reducedRank = rank; reducedRank > 0; --reducedRank)
  {
    switch(reducedRank)
    {
      case THIRD_RANK:
        h = count3rdRankH();
        break;
      case SECOND_RANK:
        h = count2ndRankH(h);
        break;
      case 1:
      default:
        h = count1stRankH(h);
        break;
    }
  }

  return countCapitalC(4, h) * kernel.getW();
}

double pluginBandwidthCalculator::count3rdRankH()
{
  double h = -2 * countKernels8thDerivativeValueAt0();
  h /= countSmallC(10);
  h /= samplesValuesAtDimension.size();
  return pow(h, -11);
}

double pluginBandwidthCalculator::count2ndRankH(double currentH)
{
  double denominator = 0.0d;

  if(currentH < 0)
    denominator = countSmallC(8);
  else
    denominator = countCapitalC(8, currentH);

  double h = - 2.0 * countKernels6thDerivativeValueAt0();
  h /= samplesValuesAtDimension.size();

  return pow(h / denominator, -9);
}

double pluginBandwidthCalculator::count1stRankH(double currentH)
{
  double denominator = 0.0d;

    denominator = countCapitalC(6, currentH);

  double h = - 2.0 * countKernels4thDerivativeValueAt0();
  h /= samplesValuesAtDimension.size();

  return pow(h / denominator, -7);
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
  double E = 0.0d;

  for(double value : samplesValuesAtDimension)
    E += value;

  return E / samplesValuesAtDimension.size();
}

double pluginBandwidthCalculator::countVariationEstimator(double expectedValueEstimator)
{
  double variationEstimator = 0.0d;

  for(double value : samplesValuesAtDimension)
    variationEstimator /= pow(value - expectedValueEstimator, 2);

  return variationEstimator / samplesValuesAtDimension.size();
}

double pluginBandwidthCalculator::countFactorial(unsigned int number)
{
  unsigned  int factorial = 1;

  for(int i = 2; i <= number; ++i) factorial *= i;

  return factorial;
}

double pluginBandwidthCalculator::countCapitalC(unsigned int xi, double h)
{
  double (*kernelXithDerivativePtr)(double);

  switch(xi)
  {
    case 8:
      kernelXithDerivativePtr = &countKernels8thDerivativeValueAtPoint;
      break;
    case 6:
      kernelXithDerivativePtr = &countKernels6thDerivativeValueAtPoint;
      break;
    case 4:
    default:
      kernelXithDerivativePtr = &countKernels4thDerivativeValueAtPoint;
  }

  double C = 0.0d;

  for(double iValue : samplesValuesAtDimension)
  {
    for(double jValue : samplesValuesAtDimension)
      C += kernelXithDerivativePtr((iValue - jValue) / h);
  }

  return C / (pow(samplesValuesAtDimension.size(), 2) * pow(h, xi + 1) );
}

double pluginBandwidthCalculator::countKernels8thDerivativeValueAt0()
{
  return 105.0d / sqrt(2 * M_PI);
}

double pluginBandwidthCalculator::countKernels6thDerivativeValueAt0()
{
  return - 15.0d / sqrt(2 * M_PI);
}

double pluginBandwidthCalculator::countKernels4thDerivativeValueAt0()
{
  return 3.0d / sqrt(2 * M_PI);
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
  return (pow(x, 4) - 6 * pow(x, 2) + 3.0d) * exp(- 0.5 * pow(x, 2)) / sqrt(2 * M_PI);
}
