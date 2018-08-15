#include "gtest/gtest.h"

#include "../../../src/kernels/productKernel.h"
#include "../../../src/kernels/normalKernel.h"
#include "../../../src/kernels/epanecznikowKernel.h"
#include "../../../src/kernels/triangularKernel.h"
#include "../../../src/kernels/linearKernel.h"

#include <ctime>
#include <random>

class productKernelFixture : public ::testing::Test
{
 protected:

  functionPtr kernel;

  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution;

  double eps = 1e-5;
  double random = 0.0;

  std::vector<double> args, symArgs, mSymArgs;

  void SetUp() override
  {
    kernelPtr nKernel = std::make_shared<normalKernel>(),
              eKernel = std::make_shared<epanecznikowKernel>(),
              tKernel = std::make_shared<triangularKernel>(),
              lKernel = std::make_shared<linearKernel>();

    std::vector<kernelPtr> kernels = {nKernel, eKernel, tKernel, lKernel};

    kernel = std::make_shared<productKernel>(kernels);

    distribution = std::uniform_real_distribution(-10.0, 10.0);
    srand((unsigned)time(nullptr));
    random = distribution(generator);
    args =  {0.0, 0.0, 0.0, 0.0, -1.0, random, random - 1.0, - random};
    symArgs = {0, 1, 2, 3, -4, random};
    mSymArgs = {0, -1, -2, -3, 4, -random};
  }

  void TearDown() override
  {}

};

TEST_F(productKernelFixture, non_negative_check)
{
  ASSERT_TRUE(kernel->getValue(args) >= 0.0);
}

TEST_F(productKernelFixture, symmetry_check)
{
  ASSERT_TRUE(kernel->getValue(symArgs) - kernel->getValue(mSymArgs) < eps);
}





