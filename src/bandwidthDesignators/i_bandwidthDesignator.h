#ifndef KERNELDENSITYESTIMATOR_I_BANDWIDTHDESIGNATOR_H
#define KERNELDENSITYESTIMATOR_I_BANDWIDTHDESIGNATOR_H

#include <vector>

class i_bandwidthDesignator
{
  public:
    virtual std::vector<double> getBandwidth(std::vector<std::vector<double>> samples) = 0;
};

#endif //KERNELDENSITYESTIMATOR_I_BANDWIDTHDESIGNATOR_H
