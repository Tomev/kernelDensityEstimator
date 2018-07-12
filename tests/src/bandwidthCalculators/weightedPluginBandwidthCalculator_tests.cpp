#include "gtest/gtest.h"

#include "../../../src/bandwidthCalculators/weightedPluginBandwidthCalculator.h"

#include <random>

class weightedPluginBandwidthCalculatorFixture : public ::testing::Test
{
  protected:

    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    std::uniform_real_distribution<double> weightsDistribution;

    weightedPluginBandwidthCalculator calculator;
    std::vector<std::vector<double>> samples;
    std::vector<double> weights;

    unsigned int maxSamplesSize = 100;
    unsigned int dimensionsNumber = 2;

    double eps = 1e-5;

    void SetUp() override
    {
      srand((unsigned)time(nullptr));

      distribution = std::normal_distribution(0.0, 1.0);

      samples.clear();
      weights.clear();

      for(unsigned int sampleNumber  = 0; sampleNumber < maxSamplesSize; ++sampleNumber)
      {
        samples.emplace_back(std::vector<double>());
        weights.emplace_back(weightsDistribution(generator));

        for(unsigned int dimensionNumber = 0; dimensionNumber < dimensionsNumber; ++dimensionNumber)
          samples[sampleNumber].emplace_back(distribution(generator));
      }

      calculator.setWeights(weights);
    };

    void TearDown() override {};
};

TEST_F(weightedPluginBandwidthCalculatorFixture, second_rank_larger_than_zero)
{
  calculator.setRank(SECOND_RANK);
  std::vector<double> bandwidth = calculator.getBandwidth(samples);
  ASSERT_TRUE(bandwidth[0] > 0.0);
}

TEST_F(weightedPluginBandwidthCalculatorFixture, third_rank_larger_than_zero)
{
  calculator.setRank(THIRD_RANK);
  std::vector<double> bandwidth = calculator.getBandwidth(samples);
  ASSERT_TRUE(bandwidth[0] > 0.0);
}

TEST_F(weightedPluginBandwidthCalculatorFixture, third_rank_lower_than_one)
{
  calculator.setRank(THIRD_RANK);
  std::vector<double> bandwidth = calculator.getBandwidth(samples);
  ASSERT_TRUE(bandwidth[0] > 0.0);
}

TEST_F(weightedPluginBandwidthCalculatorFixture, second_rank_lower_than_one)
{
  calculator.setRank(SECOND_RANK);
  std::vector<double> bandwidth = calculator.getBandwidth(samples);
  ASSERT_TRUE(bandwidth[0] > 0.0);
}

TEST_F(weightedPluginBandwidthCalculatorFixture, returns_proper_dimension_number)
{
  calculator.setRank(SECOND_RANK);
  ASSERT_TRUE(calculator.getBandwidth(samples).size() == dimensionsNumber);
}

TEST_F(weightedPluginBandwidthCalculatorFixture, setting_not_expected_rank_results_in_default)
{
  calculator.setRank(100);
  double valueToTest = calculator.getBandwidth(samples)[0];
  calculator.setRank(SECOND_RANK);
  ASSERT_TRUE(valueToTest - calculator.getBandwidth(samples)[0] < eps);
}

TEST_F(weightedPluginBandwidthCalculatorFixture, weights_and_empty_weights_has_different_results)
{
  std::vector<double> zeroWeights = {};
  calculator.setWeights(zeroWeights);
  double emptyWeightSetValue = calculator.getBandwidth(samples)[0];

  calculator.setWeights(weights);
  double fullWeightSetValue = calculator.getBandwidth(samples)[0];

  ASSERT_TRUE(fullWeightSetValue != emptyWeightSetValue);
}