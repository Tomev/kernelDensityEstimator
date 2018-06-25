#ifndef KERNELDENSITYESTIMATOR_DULLKERNEL_H
#define KERNELDENSITYESTIMATOR_DULLKERNEL_H

#include "../interfaces/i_kernel.h"

class linearKernel : public i_kernel
{
  public:
    linearKernel();

    using i_kernel::getValue;

    double getValue(double arg) override;
    double getW() override;
    double getU() override;
    double getValue(std::vector<double> args) override;
};

#endif //KERNELDENSITYESTIMATOR_DULLKERNEL_H
