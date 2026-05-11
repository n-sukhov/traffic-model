#include "equal_model.h"
#include <stdexcept>

EqualModel::EqualModel(double interval_sec, uint32_t size_bytes) :
    TrafficModel("equal"),
    interval(interval_sec),
    packet_size(size_bytes) {
    if (interval_sec <= 0.0) {
        throw std::invalid_argument("Equal: interval time must be positive");
    }
}

std::vector<Packet> EqualModel::simulate(double simulation_time) {
    std::vector<Packet> packets;
    
    if (simulation_time <= 0.0 || packet_size == 0) {
        return packets;
    }

    for (double cur_t = interval; cur_t <= simulation_time; cur_t += interval) {
        packets.push_back(Packet{ cur_t, packet_size });
    }

    return packets;
}