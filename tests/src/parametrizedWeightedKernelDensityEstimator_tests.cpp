#include "gtest/gtest.h"

#include "../../src/parametrizedWeightedKernelDensityEstimator.h"

#include <ctime>
#include <random>

class parametrizedWeightedKernelDensityEstimatorFixture : public ::testing::Test
{
 protected:
  std::default_random_engine generator;
  std::uniform_real_distribution<double> bandwidthDistribution;
  std::uniform_real_distribution<double> weightsDistribution;
  std::normal_distribution<double> samplesDistribution;
  std::uniform_real_distribution<double> paramsDistribution;
  std::uniform_int_distribution<int> intDistribution;

  unsigned int dimensionsNumber = 5;
  unsigned int samplesNumber = 100;

  PWKDEPtr estimator;

  std::vector<double> args = {};
  std::vector<double> negativeParameters = {};
  std::vector<double> positiveParameters = {};

  void SetUp() override
  {
    bandwidthDistribution = std::uniform_real_distribution<double>(0.3, 0.6);
    weightsDistribution = std::uniform_real_distribution<double>(0.0, 1.0);
    samplesDistribution = std::normal_distribution<double>(0.0, 1.0);
    paramsDistribution = std::uniform_real_distribution<double>(0.0, 1.0);
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

    estimator = std::make_shared<parametrizedWeightedKernelDensityEstimator>(prodKernel);
    estimator->setBandwidth(bandwidth);

    std::vector<std::vector<double>> samples = {};
    std::vector<double> weights = {};


    unsigned int currentSampleIndex = 0;
    double parameter = 0.0;

    // Get some samples
    while(samples.size() < samplesNumber)
    {
      samples.emplace_back(std::vector<double>());

      while(samples[currentSampleIndex].size() < dimensionsNumber)
        samples[currentSampleIndex].push_back(samplesDistribution(generator));

      weights.emplace_back(weightsDistribution(generator));

      parameter = paramsDistribution(generator);
      negativeParameters.emplace_back(-parameter);
      positiveParameters.emplace_back(parameter);

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

TEST_F(parametrizedWeightedKernelDensityEstimatorFixture, positive_params_check)
{
  estimator->setAdditionalParameters(positiveParameters);
  ASSERT_TRUE(estimator->getValue(args) >= 0.0);
}

TEST_F(parametrizedWeightedKernelDensityEstimatorFixture, negative_params_check)
{
  estimator->setAdditionalParameters(negativeParameters);
  ASSERT_TRUE(estimator->getValue(args) <= 0.0);
}




