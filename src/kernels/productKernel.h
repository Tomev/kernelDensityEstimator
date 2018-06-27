#ifndef KERNELDENSITYESTIMATOR_PRODUCTKERNEL_H
#define KERNELDENSITYESTIMATOR_PRODUCTKERNEL_H

#include "../../interfaces/i_function.h"
#include "../../interfaces/i_kernel.h"

class productKernel : public i_function
{
  public:
    explicit productKernel(std::vector<kernelPtr> kernels);

    double getValue(std::vector<double> args) override;

  protected:
    std::vector<kernelPtr> kernels;

};


#endif //KERNELDENSITYESTIMATOR_PRODUCTKERNEL_H
