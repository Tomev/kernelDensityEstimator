#ifndef KERNELDENSITYESTIMATOR_EPANECZNIKOWKERNEL_H
#define KERNELDENSITYESTIMATOR_EPANECZNIKOWKERNEL_H

#include "../interfaces/i_kernel.h"

class epanecznikowKernel : public i_kernel
{
public:
  epanecznikowKernel();

  double getValue(std::vector<double> args) override;

  double getW() override;

  double getU() override;

  double getValue(double arg) override;
};


#endif //KERNELDENSITYESTIMATOR_EPANECZNIKOWKERNEL_H
