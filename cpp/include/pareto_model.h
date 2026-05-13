#pragma once

#include "traffic_model.h"
#include <memory>
#include <string>
#include <random>

class ParetoModel : public TrafficModel {
private:
    double min_interval;
    double shape;
    uint32_t packet_size;
    std::uniform_real_distribution<double> uniform_dist;

public:
    ParetoModel(double min_interval_sec, double shape_param, uint32_t size_bytes);
    static std::unique_ptr<TrafficModel> create_from_parameters_line(const std::string& parameters);
    std::vector<Packet> simulate(double simulation_time) override;
};