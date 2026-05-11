#pragma once
#include "traffic_model.h"

class EqualModel : public TrafficModel {
private:
    double interval;
    uint32_t packet_size;

public:
    EqualModel(double interval_sec, uint32_t size_bytes);
    std::vector<Packet> simulate(double simulation_time) override;
};