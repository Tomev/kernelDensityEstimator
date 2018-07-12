#include "weightedPluginBandwidthCalculator.h"

#include <cmath>

std::vector<double> weightedPluginBandwidthCalculator::getBandwidth(std::vector<std::vector<double>> samples)
{
  overallWeight = 0.0;
  for(double weight : weights) overallWeight += weight;

  std::vector<double> bandwidth = pluginBandwidthCalculator::getBandwidth(samples);

  return bandwidth;
}

void weightedPluginBandwidthCalculator::setWeights(std::vector<double> newWeights)
{
  weights = newWeights;
}

double weightedPluginBandwidthCalculator::count3rdRankH()
{
  if(weights.empty())
    return pluginBandwidthCalculator::count3rdRankH();

  double h = -2 * countKernels8thDerivativeValueAtPoint(0);
  h /= countSmallC(10);
  h /= overallWeight;

  int sigH = h < 0 ? -1 : 1;

  h = pow(fabs(h), 1.0/11.0);
  h *= sigH;

  return h;
}

double weightedPluginBandwidthCalculator::count2ndRankH(double currentH)
{
  if(weights.empty())
    return pluginBandwidthCalculator::count2ndRankH(currentH);

  double denominator = 0.0;

  if(currentH < 0)
    denominator = countSmallC(8);
  else
    denominator = countCapitalC(8, currentH);

  double h = - 2.0 * countKernels6thDerivativeValueAtPoint(0);
  h /= overallWeight * denominator;

  return pow(h, 1.0/9.0);
}

double weightedPluginBandwidthCalculator::count1stRankH(double currentH)
{
  if(weights.empty())
    return pluginBandwidthCalculator::count1stRankH(currentH);

  double h = - 2.0 * countKernels4thDerivativeValueAtPoint(0);
  h /= overallWeight;
  h /= countCapitalC(6, currentH);
  return pow(h, 1.0/7.0);
}

double weightedPluginBandwidthCalculator::countExpectedValueEstimator()
{
  if(weights.empty())
    return pluginBandwidthCalculator::countExpectedValueEstimator();

  double E = 0.0;

  for(unsigned int i = 0; i < samplesValuesAtDimension.size(); ++i)
    E += samplesValuesAtDimension[i] * weights[i];

  E /= overallWeight;

  return E;
}

double weightedPluginBandwidthCalculator::countVariationEstimator(double expectedValueEstimator)
{
  if(weights.empty())
    return pluginBandwidthCalculator::countVariationEstimator(expectedValueEstimator);

  double variationEstimator = 0.0;

  for(unsigned int i = 0; i < samplesValuesAtDimension.size(); ++i)
    variationEstimator += pow(samplesValuesAtDimension[i] - expectedValueEstimator, 2) * weights[i];

  variationEstimator /= overallWeight;

  return variationEstimator;
}

double weightedPluginBandwidthCalculator::countCapitalC(unsigned int xi, double h)
{
  if(weights.empty())
    return pluginBandwidthCalculator::countCapitalC(xi, h);

  double (weightedPluginBandwidthCalculator::*kernelXithDerivativePtr)(double);

  switch(xi)
  {
    case 8:
      kernelXithDerivativePtr = &weightedPluginBandwidthCalculator::countKernels8thDerivativeValueAtPoint;
      break;
    case 6:
      kernelXithDerivativePtr = &weightedPluginBandwidthCalculator::countKernels6thDerivativeValueAtPoint;
      break;
    case 4:
    default:
      kernelXithDerivativePtr = &weightedPluginBandwidthCalculator::countKernels4thDerivativeValueAtPoint;
  }

  double C = 0.0;
  double addend;

  for(unsigned int i = 0; i < samplesValuesAtDimension.size(); ++i)
  {
    for(unsigned int j = 0; j < samplesValuesAtDimension.size(); ++j)
    {
      addend = (*this.*kernelXithDerivativePtr)((samplesValuesAtDimension[i] - samplesValuesAtDimension[j]) / h);
      addend *= weights[i] * weights[j];
      C += addend;
    }
  }

  C /= ( pow(overallWeight, 2) * pow(h, xi + 1) );

  return C;
}


