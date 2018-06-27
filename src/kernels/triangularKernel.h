#ifndef KERNELDENSITYESTIMATOR_TRIANGULARKERNEL_H
#define KERNELDENSITYESTIMATOR_TRIANGULARKERNEL_H

#include "../../interfaces/i_kernel.h"

class triangularKernel : public i_kernel
{
  public:
    triangularKernel();

    double getW() override;
    double getU() override;
    double getValue(double arg) override;
    double getValue(std::vector<double> args) override;
};


#endif //KERNELDENSITYESTIMATOR_TRIANGULARKERNEL_H
