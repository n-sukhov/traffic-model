#include "model_factory.h"

#include "equal_model.h"
#include "poisson_model.h"
#include <stdexcept>
#include <string>

const std::string SEPARATOR = ":";

std::unique_ptr<TrafficModel> create_model_from_line(const std::string& model_line) {
    /* Принимает сроку с информацией о модели и её параметрах, на основе неё
    создает объект модели, передает ей параметры и возвращает указатель на неё
    */
    size_t sep_idx = model_line.find(SEPARATOR);

    if (sep_idx == std::string::npos) {
        throw std::runtime_error("Model line must contain '" + SEPARATOR + "'");
    }

    std::string model_name = model_line.substr(0, sep_idx);
    std::string model_parameters = model_line.substr(sep_idx + 1);

    if (model_name == "equal") {
        return EqualModel::create_from_parameters_line(model_parameters);
    }
    if (model_name == "poisson") {
        return PoissonModel::create_from_parameters_line(model_parameters);
    }

    throw std::runtime_error("Unknown traffic model: " + model_name);
}