#include "pareto_model.h"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <sstream>

ParetoModel::ParetoModel(
    double min_interval_sec,
    double shape_param,
    uint32_t size_bytes
) :
    TrafficModel("pareto"),
    min_interval(min_interval_sec),
    shape(shape_param),
    packet_size(size_bytes),
    uniform_dist(0.0, 1.0) {
    if (min_interval_sec <= 0.0) {
        throw std::invalid_argument("Pareto: min interval must be positive");
    }
    if (shape_param <= 0.0) {
        throw std::invalid_argument("Pareto: shape parameter must be positive");
    }
    if (size_bytes == 0) {
        throw std::invalid_argument("Pareto: packet size must be positive");
    }
}

std::unique_ptr<TrafficModel> ParetoModel::create_from_parameters_line(
    const std::string& parameters
) {
    /* Принимает строку параметров из файла, и на основе неё
    создает объект
    */
    std::istringstream iss(parameters);

    double min_interval;
    double shape;
    uint32_t packet_size;

    if (!(iss >> min_interval >> shape >> packet_size)) {
        throw std::runtime_error("Invalid pareto model parameters");
    }

    return std::make_unique<ParetoModel>(min_interval, shape, packet_size);
}

std::vector<Packet> ParetoModel::simulate(double simulation_time) {
    /*Принимает на вход время симуляции, возвращает массив
    структур с данными о переданных пакетах
    */
    std::vector<Packet> packets;

    if (simulation_time <= 0.0) {
        return packets;
    }

    double current_time = 0.0;

    while (current_time <= simulation_time) {
        double ud = uniform_dist(rand_gen);
        if (ud <= 0.0) {
            ud = std::numeric_limits<double>::min();
        }

        double interval = min_interval / std::pow(ud, 1.0 / shape);
        current_time += interval;
        if (current_time > simulation_time) { break; }

        packets.push_back(Packet{ current_time, packet_size });
    }

    return packets;
}