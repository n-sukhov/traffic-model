#pragma once

#include "traffic_model.h"
#include <memory>
#include <string>

std::unique_ptr<TrafficModel> create_model_from_line(const std::string& model_line);