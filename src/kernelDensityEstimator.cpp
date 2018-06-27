#include "kernelDensityEstimator.h"

kernelDensityEstimator::kernelDensityEstimator(functionPtr kernel) : estimatorKernel(kernel){}


/** Returns value of KDE in given point. Note that it assumes that settings are correct, specifically dimensionality of
 *  given point, bandwidth size and number of kernels (contract programming).
 *
 *  @brief Returns value of KDE in given point.
 *
 *  @param Vector of real values.
 *
 *  @return Value of KDE in given point.
 */
double kernelDensityEstimator::getValue(std::vector<double> args)
{
  double result = 0.0f;

  std::vector<double> kernelArgs = {};
  double kernelArg = 0.0f;

  for(std::vector<double> sample : samples)
  {
    kernelArgs = {};

    for (unsigned int i = 0; i < args.size(); ++i)
    {
      kernelArg = args[i] - sample[i];
      kernelArg /= bandwidth[i];
      kernelArgs.push_back(kernelArg);
    }

    result += estimatorKernel->getValue(kernelArgs);
  }


  for(double h : bandwidth)
    result /= h;

  return result / samples.size();
}

void kernelDensityEstimator::setBandwidth(std::vector<double> newBandwidth)
{
  bandwidth = newBandwidth;
}

void kernelDensityEstimator::setSamples(std::vector<std::vector<double>> newSamples)
{
  samples = newSamples;
}



