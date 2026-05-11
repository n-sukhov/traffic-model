#pragma once

#include <string>
#include <random>
#include <cstdint>


struct packet {
    uint32_t size;
    double arrival_time;
};

class TrafficModel {
protected:
    std::string model_name;
    std::mt19937 rand_gen;

public:
    TrafficModel(const std::string& name) : model_name(name) {
        std::random_device rd;
        rand_gen = std::mt19937(rd());
    }
    virtual ~TrafficModel();
    virtual packet generate_next_packet(double current_time) = 0;
    virtual std::string get_modeal_name() const { return model_name; }
};