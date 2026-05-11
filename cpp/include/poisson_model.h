#pragma once
#include "traffic_model.h"

class PoissonModel : public TrafficModel {
private:
    std::poisson_distribution<int> interval_dist; // для задержек
    std::exponential_distribution<double> size_dist; // для размеров
    uint32_t mtu; // Maximum transmission unit

public:
    PoissonModel(double interval_lambda, double size_lambda, uint32_t max_trans_unit);
    std::vector<Packet> simulate(double simulation_time) override;
};
