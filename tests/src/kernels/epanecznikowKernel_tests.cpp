#include "gtest/gtest.h"

#include "../../../kernels/epanecznikowKernel.h"

#include <ctime>
#include <random>

class epanecznikowKernelFixture : public ::testing::Test
{
protected:
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution;

  double eps = 1e-5;
  double random = 0.0;
  epanecznikowKernel kernel;

  void SetUp() override
  {
    distribution = std::uniform_real_distribution(-10.0, 10.0);
    srand((unsigned)time(nullptr));
    random = distribution(generator);
  }

  void TearDown() override
  {}

};

TEST_F(epanecznikowKernelFixture, max_in_zero_check)
{
  ASSERT_TRUE(kernel.getValue(0.0) >= kernel.getValue(random));
}

TEST_F(epanecznikowKernelFixture, symmetry_check)
{
  ASSERT_TRUE(kernel.getValue(random) - kernel.getValue(-random) < eps);
}

TEST_F(epanecznikowKernelFixture, greater_than_or_equal_to_0)
{
  ASSERT_FALSE(kernel.getValue(random) < 0.0f);
}

