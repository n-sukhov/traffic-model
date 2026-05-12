#include "utils.h"
#include "model_factory.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }
    
    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        throw std::runtime_error("Can't open input file");
    }
    double simulation_time;
    input_file >> simulation_time;

    std::string model_line;
    std::getline(input_file, model_line);
    std::getline(input_file, model_line);

    std::unique_ptr<TrafficModel> model = create_model_from_line(model_line);
    std::vector<Packet> packets = model->simulate(simulation_time);

    write_packets_to_csv(
        model->get_model_name() + "_traffic.csv",
        packets
    );

    return 0;
}