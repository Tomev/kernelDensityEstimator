#ifndef KERNELDENSITYESTIMATOR_WEIGHTEDKERNELDENSITYESTIMATOR_H
#define KERNELDENSITYESTIMATOR_WEIGHTEDKERNELDENSITYESTIMATOR_H

#include "kernelDensityEstimator.h"

class weightedKernelDensityEstimator : public kernelDensityEstimator
{
  public:
    explicit weightedKernelDensityEstimator(functionPtr kernel);

    void setWeights(std::vector<double> newWeights);

    double getValue(std::vector<double> args) override;

  protected:
    std::vector<double> weights;
};

typedef std::shared_ptr<weightedKernelDensityEstimator> WKDEPtr;

#endif //KERNELDENSITYESTIMATOR_WEIGHTEDKERNELDENSITYESTIMATOR_H
