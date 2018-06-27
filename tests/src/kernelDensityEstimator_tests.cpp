#include "gtest/gtest.h"

#include "../../src/kernelDensityEstimator.h"

#include <ctime>
#include <random>

class kernelDensityEstimatorFixture : public ::testing::Test
{
 protected:
  std::default_random_engine generator;
  std::uniform_real_distribution<double> bandwidthDistribution;
  std::normal_distribution<double> samplesDistribution;
  std::uniform_int_distribution<int> intDistribution;

  unsigned int dimensionsNumber = 5;
  unsigned int samplesNumber = 100;

  KDEPtr estimator;

  std::vector<double> args = {};

  void SetUp() override
  {
    bandwidthDistribution = std::uniform_real_distribution<double>(0.3d, 0.6d);
    samplesDistribution = std::normal_distribution<double>(0.0d, 1.0d);
    intDistribution = std::uniform_int_distribution<int> (0, 4);

    srand((unsigned)time(nullptr));

    std::vector<kernelPtr> kernels = {};
    std::vector<double> bandwidth = {};

    // Get some random kernels and bandwidths
    while(kernels.size() < dimensionsNumber)
    {
      kernels.push_back(getRandomKernel());
      bandwidth.push_back(bandwidthDistribution(generator));
    }

    functionPtr prodKernel = std::make_shared<productKernel>(kernels);

    estimator = std::make_shared<kernelDensityEstimator>(prodKernel);
    estimator->setBandwidth(bandwidth);

    std::vector<std::vector<double>> samples = {};
    unsigned int currentSampleIndex = 0;

    // Get some samples
    while(samples.size() < samplesNumber)
    {
      samples.emplace_back({});

      while(samples[currentSampleIndex].size() < dimensionsNumber)
        samples[currentSampleIndex].push_back(samplesDistribution(generator));

      ++currentSampleIndex;
    }

    estimator->setSamples(samples);

    // Create random sample
    while(args.size() < dimensionsNumber)
      args.push_back(samplesDistribution(generator));
  }

  void TearDown() override
  {}

  kernelPtr getRandomKernel()
  {
    int kernelID = intDistribution(generator);

    switch(kernelID)
    {
      case EPANECZNIKOW:
        return std::make_shared<epanecznikowKernel>();
      case NORMAL:
        return std::make_shared<normalKernel>();
      case TRIANGULAR:
        return std::make_shared<triangularKernel>();
      case LINEAR:
      default:
        return std::make_shared<linearKernel>();
    }
  }

};

TEST_F(kernelDensityEstimatorFixture, greater_than_or_equal_to_0)
{
  ASSERT_TRUE(estimator->getValue(args) >= 0.0d);
}



