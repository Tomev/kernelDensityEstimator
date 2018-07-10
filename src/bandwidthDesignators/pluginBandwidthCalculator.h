#ifndef KERNELDENSITYESTIMATOR_PLUGINBANDWIDTHDESIGNATOR_H
#define KERNELDENSITYESTIMATOR_PLUGINBANDWIDTHDESIGNATOR_H

#include "i_bandwidthCalculator.h"
#include "../kernels/normalKernel.h"

class pluginBandwidthCalculator : public i_bandwidthCalculator
{
  public:
    std::vector<double> getBandwidth(std::vector<std::vector<double>> samples) override;

  protected:

    unsigned int rank = 2;
    normalKernel kernel; /// Standard kernel for plugin bandwidth designator.

    double getRankedBandwidthAtGivenDimension(std::vector<double> samplesValuesAtDimension);
    double countSmallC(unsigned int xi);
    double countFactorial(unsigned int number);

    /// Knowing that normal kernel is used, it's n-th derivatives at 0 are calculated using simplified formulas
    double getKernels8thDerivativeValueAt0();
    double getKernels6thDerivativeValueAt0();
    double getKernels4thDerivativeValueAt0();

};

enum pluginRanks
{
  SECOND_RANK = 2,
  THIRD_RANK = 3
};

#endif //KERNELDENSITYESTIMATOR_PLUGINBANDWIDTHDESIGNATOR_H
