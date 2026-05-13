#pragma once

#include "traffic_model.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


const std::string DATA_FOLDER = "data/";

inline std::string format_double(double x, int precision) {
    // Форматирование double для записи в названия файлов с заданной точностью
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << x;
    return out.str();
}

inline void ensure_data_dir(const std::string& data_dir) {
    // Проверка наличия папки для сохранения данных / её создание
    if (!std::filesystem::exists(data_dir)) {
        std::filesystem::create_directories(data_dir);
    }
}

inline void write_packets_to_csv(
    const std::string& filename,
    const std::vector<Packet>& packets
) {
    // Для записи данных с симуляции в csv
    ensure_data_dir(DATA_FOLDER);

    std::string file_path = DATA_FOLDER + filename;

    std::ofstream file(file_path);

    if (!file.is_open()) {
        throw std::runtime_error("Can't open file: " + file_path);
    }

    for (const Packet& packet : packets) {
        file << packet.arrival_time << "," << packet.size << "\n";
    }
}