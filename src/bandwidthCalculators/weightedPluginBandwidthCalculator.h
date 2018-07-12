#ifndef KERNELDENSITYESTIMATOR_WEIGHTEDPLUGINBANDWIDTHCALCULATOR_H
#define KERNELDENSITYESTIMATOR_WEIGHTEDPLUGINBANDWIDTHCALCULATOR_H

#include "pluginBandwidthCalculator.h"

class weightedPluginBandwidthCalculator : public pluginBandwidthCalculator
{
  public:
    weightedPluginBandwidthCalculator() = default;

    std::vector<double> getBandwidth(std::vector<std::vector<double>> samples) override;

    void setWeights(std::vector<double> newWeights);

  protected:

    std::vector<double> weights;
    double overallWeight = 0.0;

    double count3rdRankH() override;
    double count2ndRankH(double currentH) override;
    double count1stRankH(double currentH) override;
    double countExpectedValueEstimator() override;
    double countVariationEstimator(double expectedValueEstimator) override;
    double countCapitalC(unsigned int xi, double h) override;

};

#endif //KERNELDENSITYESTIMATOR_WEIGHTEDPLUGINBANDWIDTHCALCULATOR_H
