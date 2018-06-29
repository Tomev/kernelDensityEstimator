#include "parametrizedWeightedKernelDensityEstimator.h"

parametrizedWeightedKernelDensityEstimator::parametrizedWeightedKernelDensityEstimator(functionPtr kernel)
    : weightedKernelDensityEstimator(kernel) {}

/** Returns value of parametrized weighted KDE in given point. Note that it assumes that settings are correct,
 *  specifically dimensionality of given point, bandwidth size, weights or parameters number and number of kernels
 *  (contract programming). This kind of KDE can be used e.g. to estimate data changes dynamics.
 *
 *  @brief Returns value of parametrized weighted KDE in given point.
 *
 *  @param Vector of real values.
 *
 *  @return Value of parametrized weighted KDE in given point.
 */
double parametrizedWeightedKernelDensityEstimator::getValue(std::vector<double> args)
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

    result += estimatorKernel->getValue(kernelArgs) * weights[i] * additionalParameters[i];
  }


  for(double h : bandwidth)
    result /= h;

  for(double weight : weights)
    result /= weight;

  return result;
}
void parametrizedWeightedKernelDensityEstimator::setAdditionalParameters(std::vector<double> newAdditionalParameters)
{
  additionalParameters = newAdditionalParameters;
}

