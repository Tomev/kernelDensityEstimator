#ifndef KERNELDENSITYESTIMATOR_NORMALKERNEL_H
#define KERNELDENSITYESTIMATOR_NORMALKERNEL_H

#include "../interfaces/i_kernel.h"

/// Class representing normal distribution.
class normalKernel : public i_kernel
{
  public:
    normalKernel();
    explicit normalKernel(double stdDev);

    double getValue(double arg) override;
    double getValue(std::vector<double> args) override;
    double getW() override;
    double getU() override;

  protected:
    double stdDev = 0.0;


};

#endif //KERNELDENSITYESTIMATOR_NORMALKERNEL_H
