#ifndef KERNELDENSITYESTIMATOR_I_BANDWIDTHCALCULATOR_H
#define KERNELDENSITYESTIMATOR_I_BANDWIDTHCALCULATOR_H

#include <vector>
#include <memory>

class i_bandwidthCalculator
{
  public:
    virtual std::vector<double> getBandwidth(std::vector<std::vector<double>> samples) = 0;
};

typedef std::shared_ptr<i_bandwidthCalculator> bandwidthCalculatorPtr;

#endif //KERNELDENSITYESTIMATOR_I_BANDWIDTHCALCULATOR_H
