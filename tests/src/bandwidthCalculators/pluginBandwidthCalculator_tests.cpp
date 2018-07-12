#include "gtest/gtest.h"

#include "../../../src/bandwidthCalculators/pluginBandwidthCalculator.h"

#include <random>

class pluginBandwidthCalculatorFixture : public ::testing::Test
{
  protected:

    std::default_random_engine generator;
    std::normal_distribution<double> distribution;

    pluginBandwidthCalculator calculator;
    std::vector<std::vector<double>> samples;

    unsigned int maxSamplesSize = 100;
    unsigned int dimensionsNumber = 2;

    void SetUp() override
    {
      srand((unsigned)time(nullptr));

      distribution = std::normal_distribution(0.0d, 1.0d);

      samples.clear();

      for(unsigned int sampleNumber  = 0; sampleNumber < maxSamplesSize; ++sampleNumber)
      {
        samples.emplace_back(std::vector<double>());

        for(unsigned int dimensionNumber = 0; dimensionNumber < dimensionsNumber; ++dimensionNumber)
          samples[sampleNumber].emplace_back(distribution(generator));
      }
    };

    void TearDown() override {};
};

TEST_F(pluginBandwidthCalculatorFixture, second_rank_larger_than_zero)
{
  calculator.setRank(2);
  std::vector<double> bandwidth = calculator.getBandwidth(samples);
  ASSERT_TRUE(bandwidth[0] > 0.0d);
}

TEST_F(pluginBandwidthCalculatorFixture, third_rank_larger_than_zero)
{
  calculator.setRank(3);
  std::vector<double> bandwidth = calculator.getBandwidth(samples);
  ASSERT_TRUE(bandwidth[0] > 0.0d);
}

TEST_F(pluginBandwidthCalculatorFixture, returns_proper_dimension_number)
{
  calculator.setRank(2);
  ASSERT_TRUE(calculator.getBandwidth(samples).size() == dimensionsNumber);
}