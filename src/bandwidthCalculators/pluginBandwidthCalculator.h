#ifndef KERNELDENSITYESTIMATOR_PLUGINBANDWIDTHCALCULATOR_H
#define KERNELDENSITYESTIMATOR_PLUGINBANDWIDTHCALCULATOR_H

#include "i_bandwidthCalculator.h"
#include "../kernels/normalKernel.h"

class pluginBandwidthCalculator : public i_bandwidthCalculator
{
  public:
    pluginBandwidthCalculator() = default;

    std::vector<double> getBandwidth(std::vector<std::vector<double>> samples) override;

    void setRank(unsigned int newRank);

  protected:

    unsigned int rank = 2;
    normalKernel kernel; /// Standard kernel for plugin bandwidth designator.

    std::vector<std::vector<double>> samples;
    std::vector<double> samplesValuesAtDimension;

    double getRankedBandwidthAtGivenDimension();
    virtual double count3rdRankH();
    virtual double count2ndRankH(double currentH);
    virtual double count1stRankH(double currentH);
    virtual double countSmallC(unsigned int xi);
    double countStandardDeviationEstimator();
    virtual double countExpectedValueEstimator();
    virtual double countVariationEstimator(double expectedValueEstimator);
    virtual double countCapitalC(unsigned int xi, double h);
    double countFactorial(unsigned int number);

    /// Knowing that normal kernel is used, it's n-th derivatives at 0 are calculated using simplified formulas
    double countKernels8thDerivativeValueAtPoint(double x);
    double countKernels6thDerivativeValueAtPoint(double x);
    double countKernels4thDerivativeValueAtPoint(double x);


};

enum pluginRanks
{
  SECOND_RANK = 2,
  THIRD_RANK = 3
};

#endif //KERNELDENSITYESTIMATOR_PLUGINBANDWIDTHCALCULATOR_H
