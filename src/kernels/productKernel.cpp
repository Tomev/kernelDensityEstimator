#include "productKernel.h"

productKernel::productKernel(std::vector<i_kernel> kernels) : kernels(kernels){}

double productKernel::getValue(std::vector<double> args)
{
  double product = 1.0f;

  for(unsigned int i = 0; i < kernels.size(); ++i)
    product *= kernels[i].getValue(args[i]);

  return product;
}

