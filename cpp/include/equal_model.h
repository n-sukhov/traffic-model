#pragma once
#include "traffic_model.h"
#include <memory>
#include <string>

class EqualModel : public TrafficModel {
private:
    double interval;
    uint32_t packet_size;

public:
    EqualModel(double interval_sec, uint32_t size_bytes);
    static std::unique_ptr<TrafficModel> create_from_parameters_line(const std::string& parameters);
    std::vector<Packet> simulate(double simulation_time) override;
};