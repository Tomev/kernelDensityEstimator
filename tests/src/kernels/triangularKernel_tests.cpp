#include "gtest/gtest.h"

#include "../../../kernels/triangularKernel.h"

#include <ctime>
#include <random>

class triangularKernelFixture : public ::testing::Test
{
protected:
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution;

  double eps = 1e-5;
  double random = 0.0;
  triangularKernel kernel;

  std::vector<double> args;

  void SetUp() override
  {
    distribution = std::uniform_real_distribution(-10.0, 10.0);
    srand((unsigned)time(nullptr));
    random = distribution(generator);
    args =  {0.0f, -1.0f, random, random - 1.0f};
  }

  void TearDown() override
  {}

};

TEST_F(triangularKernelFixture, max_in_zero_check)
{
  ASSERT_TRUE(kernel.getValue(0.0) >= kernel.getValue(random));
}

TEST_F(triangularKernelFixture, symmetry_check)
{
  ASSERT_TRUE(kernel.getValue(random) - kernel.getValue(-random) < eps);
}

TEST_F(triangularKernelFixture, greater_than_or_equal_to_0)
{
  ASSERT_FALSE(kernel.getValue(random) < 0.0f);
}

TEST_F(triangularKernelFixture, different_getValues_check)
{
  ASSERT_TRUE(kernel.getValue(args) - kernel.getValue(0.0f) < eps);
}

