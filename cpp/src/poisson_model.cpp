#include "poisson_model.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <sstream>

PoissonModel::PoissonModel(double interval_lambda, double size_lambda, uint32_t max_trans_unit) :
    TrafficModel("poisson"),
    interval_dist(interval_lambda),
    size_dist(size_lambda),
    mtu(max_trans_unit) {
    if (interval_lambda <= 0.0) {
        throw std::invalid_argument("Poisson: interval lambda must be positive");
    }
    if (size_lambda <= 0.0) {
        throw std::invalid_argument("Exponential size lambda must be positive");
    }
    if (mtu == 0) {
        throw std::invalid_argument("MTU must be positive");
    }
}

std::unique_ptr<TrafficModel> PoissonModel::create_from_parameters_line(
    const std::string& parameters
) {
    /* Принимает строку параметров из файла, и на основе неё
    создает объект
    */
    std::istringstream iss(parameters);

    double interval_lambda;
    double size_lambda;
    uint32_t max_trans_unit;

    if (!(iss >> interval_lambda >> size_lambda >> max_trans_unit)) {
        throw std::runtime_error("Invalid poisson model parameters");
    }

    return std::make_unique<PoissonModel>(interval_lambda, size_lambda, max_trans_unit);

}

std::vector<Packet> PoissonModel::simulate(double simulation_time) {
    /*Принимает на вход время симуляции, возвращает массив
    структур с данными о переданных пакетах
    */
    std::vector<Packet> packets;

    double current_time = 0.0;

    while (current_time <= simulation_time) {
        int interval_ticks = interval_dist(rand_gen);
        current_time += static_cast<double>(interval_ticks);

        if (current_time > simulation_time) { break; }

        uint32_t size = static_cast<uint32_t>(size_dist(rand_gen)) + 1;
        size = std::min(size, mtu);

        packets.push_back(Packet{ current_time, size });
    }

    return packets;
}