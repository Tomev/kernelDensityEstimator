#include "gtest/gtest.h"

#include "../../src/weightedKernelDensityEstimator_tests.h"

#include <ctime>
#include <random>

class weightedKernelDensityEstimatorFixture : public ::testing::Test
{
 protected:
  std::default_random_engine generator;
  std::uniform_real_distribution<double> bandwidthDistribution;
  std::uniform_real_distribution<double> weightsDistribution;
  std::normal_distribution<double> samplesDistribution;
  std::uniform_int_distribution<int> intDistribution;

  unsigned int dimensionsNumber = 5;
  unsigned int samplesNumber = 100;

  WKDEPtr estimator;

  std::vector<double> args = {};

  void SetUp() override
  {
    bandwidthDistribution = std::uniform_real_distribution<double>(0.3d, 0.6d);
    weightsDistribution = std::uniform_real_distribution<double>(0.0d, 1.0d);
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

    estimator = std::make_shared<weightedKernelDensityEstimator>(prodKernel);
    estimator->setBandwidth(bandwidth);

    std::vector<std::vector<double>> samples = {};
    std::vector<double> weights = {};

    unsigned int currentSampleIndex = 0;

    // Get some samples
    while(samples.size() < samplesNumber)
    {
      samples.emplace_back(std::vector<double>());

      while(samples[currentSampleIndex].size() < dimensionsNumber)
        samples[currentSampleIndex].push_back(samplesDistribution(generator));

      weights.emplace_back(weightsDistribution(generator));

      ++currentSampleIndex;
    }

    estimator->setSamples(samples);
    estimator->setWeights(weights);

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

TEST_F(weightedKernelDensityEstimatorFixture, greater_than_or_equal_to_0)
{
  ASSERT_TRUE(estimator->getValue(args) >= 0.0d);
}




