#include "gtest/gtest.h"

#include "../../../src/kernels/normalKernel.h"

#include <ctime>
#include <random>

class normalKernelFixture : public ::testing::Test
{
  protected:
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;

    double eps = 1e-5;
    double random = 0.0;
    normalKernel kernel;

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

TEST_F(normalKernelFixture, max_in_zero_check)
{
  ASSERT_TRUE(kernel.getValue(0.0) >= kernel.getValue(random));
}

TEST_F(normalKernelFixture, symmetry_check)
{
  ASSERT_TRUE(kernel.getValue(random) - kernel.getValue(-random) < eps);
}

TEST_F(normalKernelFixture, greater_than_0)
{
  ASSERT_TRUE(kernel.getValue(random) > 0.0f);
}

TEST_F(normalKernelFixture, different_getValues_check)
{
  ASSERT_TRUE(kernel.getValue(args) - kernel.getValue(0.0f) < eps);
}



