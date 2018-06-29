#include "weightedKernelDensityEstimator.h"

weightedKernelDensityEstimator::weightedKernelDensityEstimator(functionPtr kernel) : kernelDensityEstimator(kernel) {}

void weightedKernelDensityEstimator::setWeights(std::vector<double> newWeights)
{
  weights = newWeights;
}

/** Returns value of weighted KDE in given point. Note that it assumes that settings are correct, specifically
 *  dimensionality of given point, bandwidth size, weights number and number of kernels (contract programming).
 *
 *  @brief Returns value of weighted KDE in given point.
 *
 *  @param Vector of real values.
 *
 *  @return Value of weighted KDE in given point.
 */
double weightedKernelDensityEstimator::getValue(std::vector<double> args)
{
  double result = 0.0f;

  std::vector<double> kernelArgs = {};
  double kernelArg = 0.0f;

  for(unsigned int i = 0; i < samples.size(); ++i)
  {
    kernelArgs = {};

    for(unsigned int j = 0; j < args.size(); ++j)
    {
      kernelArg = args[j] - samples[i][j];
      kernelArg /= bandwidth[j];
      kernelArgs.push_back(kernelArg);
    }

    result += estimatorKernel->getValue(kernelArgs) * weights[i];
  }


  for(double h : bandwidth)
    result /= h;

  for(double weight : weights)
    result /= weight;

  return result;
}


