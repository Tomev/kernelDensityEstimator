#ifndef KERNELDENSITYESTIMATOR_NORMALKERNEL_H
#define KERNELDENSITYESTIMATOR_NORMALKERNEL_H

#include "../interfaces/i_kernel.h"

class normalKernel : public i_kernel
{
  public:
    normalKernel();
    explicit normalKernel(double stdDev);

    using i_kernel::getValue;

    double getValue(double arg) override;
    double getW() override;
    double getU() override;
    double getValue(std::vector<double> args) override;

  protected:
    double stdDev = 1.0;
};

#endif //KERNELDENSITYESTIMATOR_NORMALKERNEL_H
