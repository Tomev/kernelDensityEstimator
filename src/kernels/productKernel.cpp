#include "productKernel.h"


/** Constructor of product kernel. Note that empty vector can be passed, however product kernel will then only
 *  generate 0s, for any vector.
 *
 *  @brief Constructor of product kernel.
 *
 *  @param Vector of kernels.
 */
productKernel::productKernel(std::vector<kernelPtr> kernels) : kernels(kernels){}


/** Returns value of product kernel, using kernels given in constructor. Note that it doesn't check if number
 *  of args and number of kernels is equal as this should be ensured in separate method(contract programming).
 *
 *  @brief Returns value of product kernel on given vector.
 *
 *  @param Vector od doubles.
 *
 *  @return Value of product kernel on given vector.
 */
double productKernel::getValue(std::vector<double> args)
{
  double product = 1.0f;

  for(unsigned int i = 0; i < kernels.size(); ++i)
    product *= kernels[i]->getValue(args[i]);

  return product;
}

