#include "pluginBandwidthCalculator.h"

#include <math.h>


std::vector<double> pluginBandwidthCalculator::getBandwidth(std::vector<std::vector<double>> samples)
{
  std::vector<double> bandwidth = std::vector<double>();

  std::vector<double> samplesValuesAtDimension = std::vector<double>();

  for(unsigned int dimension = 0; dimension < samples[0].size(); ++dimension)
  {
    // Extract values at given dimension
    samplesValuesAtDimension.clear();

    for(std::vector<double> sample : samples)
      samplesValuesAtDimension.emplace_back(sample[dimension]);

    bandwidth.emplace_back(getRankedBandwidthAtGivenDimension(samplesValuesAtDimension));
  }

  return bandwidth;
}

/** a
 *
 *  @param samplesValuesAtDimension Values at n-th dimension of samples.
 *  @return Bandwidth value from given samples.
 */

double pluginBandwidthCalculator::getRankedBandwidthAtGivenDimension(std::vector<double> samplesValuesAtDimension)
{
  double bandwidth = 0.0d;



  return bandwidth;
}

double pluginBandwidthCalculator::countSmallC(unsigned int xi)
{
  double c = countFactorial(xi);
  c /= countFactorial(xi / 2);
  c /= sqrt(M_PI);



  return c;
}

double pluginBandwidthCalculator::countFactorial(unsigned int number) {
  unsigned  int factorial = 1;

  for(int i = 2; i <= number; ++i) factorial *= i;

  return factorial;
}

double pluginBandwidthCalculator::getKernels8thDerivativeValueAt0()
{
  return 105.0d / sqrt(2 * M_PI);
}

double pluginBandwidthCalculator::getKernels6thDerivativeValueAt0()
{
  return - 15.0d / sqrt(2 * M_PI);
}

double pluginBandwidthCalculator::getKernels4thDerivativeValueAt0()
{
  return 3.0d / sqrt(2 * M_PI);
}









