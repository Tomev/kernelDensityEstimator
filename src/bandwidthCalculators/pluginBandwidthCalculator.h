#ifndef KERNELDENSITYESTIMATOR_PLUGINBANDWIDTHDESIGNATOR_H
#define KERNELDENSITYESTIMATOR_PLUGINBANDWIDTHDESIGNATOR_H

#include "i_bandwidthCalculator.h"
#include "../kernels/normalKernel.h"

class pluginBandwidthCalculator : public i_bandwidthCalculator
{
  public:
    pluginBandwidthCalculator();
    std::vector<double> getBandwidth(std::vector<std::vector<double>> samples) override;

    void setRank(unsigned int newRank);

  protected:

    unsigned int rank = 2;
    normalKernel kernel; /// Standard kernel for plugin bandwidth designator.

    std::vector<std::vector<double>> samples;
    std::vector<double> samplesValuesAtDimension;

    double getRankedBandwidthAtGivenDimension();
    double count3rdRankH();
    double count2ndRankH(double currentH);
    double count1stRankH(double currentH);
    double countSmallC(unsigned int xi);
    double countStandardDeviationEstimator();
    double countExpectedValueEstimator();
    double countVariationEstimator(double expectedValueEstimator);
    double countCapitalC(unsigned int xi, double h);
    double countFactorial(unsigned int number);

    /// Knowing that normal kernel is used, it's n-th derivatives at 0 are calculated using simplified formulas
    double countKernels8thDerivativeValueAt0();
    double countKernels6thDerivativeValueAt0();
    double countKernels4thDerivativeValueAt0();
    double countKernels8thDerivativeValueAtPoint(double x);
    double countKernels6thDerivativeValueAtPoint(double x);
    double countKernels4thDerivativeValueAtPoint(double x);


};

enum pluginRanks
{
  SECOND_RANK = 2,
  THIRD_RANK = 3
};

#endif //KERNELDENSITYESTIMATOR_PLUGINBANDWIDTHDESIGNATOR_H