#ifndef KERNELDENSITYESTIMATOR_PRODUCTKERNEL_H
#define KERNELDENSITYESTIMATOR_PRODUCTKERNEL_H

#include "../../interfaces/i_function.h"
#include "../../interfaces/i_kernel.h"

class productKernel : public i_function
{
  public:
    productKernel(std::vector<i_kernel> kernels);

    double getValue(std::vector<double> args) override;

  protected:
    std::vector<i_kernel> kernels;

};


#endif //KERNELDENSITYESTIMATOR_PRODUCTKERNEL_H
