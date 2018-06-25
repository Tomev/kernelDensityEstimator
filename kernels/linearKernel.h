#ifndef KERNELDENSITYESTIMATOR_DULLKERNEL_H
#define KERNELDENSITYESTIMATOR_DULLKERNEL_H

#include "../interfaces/i_kernel.h"

class linearKernel : public i_kernel
{
  linearKernel();

  double getValue(double arg) override;
  double getValue(std::vector<double> args) override;
  double getW() override;
  double getU() override;

};

#endif //KERNELDENSITYESTIMATOR_DULLKERNEL_H
