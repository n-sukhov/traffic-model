#include "equal_model.h"
#include <stdexcept>
#include <sstream>

EqualModel::EqualModel(double interval_sec, uint32_t size_bytes) :
    TrafficModel("equal"),
    interval(interval_sec),
    packet_size(size_bytes) {
    if (interval_sec <= 0.0) {
        throw std::invalid_argument("Equal: interval time must be positive");
    }
}

std::unique_ptr<TrafficModel> EqualModel::create_from_parameters_line(
    const std::string& parameters
) {
    /* Принимает строку параметров из файла, и на основе неё
    создает объект
    */
    std::istringstream iss(parameters);

    double interval;
    uint32_t packet_size;

    if (!(iss >> interval >> packet_size)) {
        throw std::runtime_error("Invalid equal model parameters");
    }

    return std::make_unique<EqualModel>(interval, packet_size);
}

std::vector<Packet> EqualModel::simulate(double simulation_time) {
    /*Принимает на вход время симуляции, возвращает массив
    структур с данными о переданных пакетах
    */
    std::vector<Packet> packets;
    
    if (simulation_time <= 0.0 || packet_size == 0) {
        return packets;
    }

    for (double cur_t = interval; cur_t <= simulation_time; cur_t += interval) {
        packets.push_back(Packet{ cur_t, packet_size });
    }

    return packets;
}