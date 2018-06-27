#ifndef KERNELDENSITYESTIMATOR_KERNELDENSITYESTIMATOR_H
#define KERNELDENSITYESTIMATOR_KERNELDENSITYESTIMATOR_H

#include "../interfaces/i_function.h"
#include "kernels/kernels.h"

class kernelDensityEstimator : public i_function
{
  public:
    explicit kernelDensityEstimator(functionPtr kernel);

    double getValue(std::vector<double> args) override;
    void setBandwidth(std::vector<double> newBandwidth);
    void setSamples(std::vector<std::vector<double>> newSamples);

  protected:
    std::vector<double> bandwidth;
    std::vector<std::vector<double>> samples;
    functionPtr estimatorKernel;

};

typedef std::shared_ptr<kernelDensityEstimator> KDEPtr;

#endif //KERNELDENSITYESTIMATOR_KERNELDENSITYESTIMATOR_H
