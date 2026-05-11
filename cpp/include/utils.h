#pragma once

#include "traffic_model.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>


const std::string DATA_FOLDER = "data/";


inline void ensure_data_dir() {
    // Проверка наличия папки для сохранения данных / её создание
    if (!std::filesystem::exists(DATA_FOLDER)) {
        std::filesystem::create_directory(DATA_FOLDER);
    }
}

inline void write_packets_to_csv(
    const std::string& filename,
    const std::vector<Packet>& packets
) {
    ensure_data_dir();

    std::string file_path = DATA_FOLDER + filename;

    std::ofstream file(file_path);

    if (!file.is_open()) {
        throw std::runtime_error("Can't open file: " + file_path);
    }

    for (const Packet& packet : packets) {
        file << packet.arrival_time << "," << packet.size << "\n";
    }
}