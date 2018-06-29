#ifndef KERNELDENSITYESTIMATOR_PARAMETRIZEDWEIGHTEDKERNELDENSITYESTIMATOR_H
#define KERNELDENSITYESTIMATOR_PARAMETRIZEDWEIGHTEDKERNELDENSITYESTIMATOR_H

#include "weightedKernelDensityEstimator.h"

class parametrizedWeightedKernelDensityEstimator : public weightedKernelDensityEstimator
{
  public:
    explicit parametrizedWeightedKernelDensityEstimator(functionPtr kernel);

    double getValue(std::vector<double> args) override;
    void setAdditionalParameters(std::vector<double> newAdditionalParameters);

  protected:
    std::vector<double> additionalParameters;

};

#endif //KERNELDENSITYESTIMATOR_PARAMETRIZEDWEIGHTEDKERNELDENSITYESTIMATOR_H
