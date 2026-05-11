#pragma once

#include <string>
#include <random>
#include <cstdint>
#include <vector>


struct Packet {
    double arrival_time;
    uint32_t size;
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
    virtual ~TrafficModel() = default;

    virtual std::vector<Packet> simulate(double simulation_time) = 0;
    // Генерация пакетов за время симуляции

    virtual std::string get_model_name() const { return model_name; } // Возвращает тип модели
};