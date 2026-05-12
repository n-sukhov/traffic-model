cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_COMPILER "g++" CACHE STRING "Compiler" FORCE)
set(CMAKE_C_COMPILER "gcc" CACHE STRING "Compiler" FORCE)

project(traffic_model LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(headers_dir ./include)
set(source_dir ./src)

set(sources
    ${source_dir}/main.cpp
    ${source_dir}/equal_model.cpp
    ${source_dir}/poisson_model.cpp
    ${source_dir}/model_factory.cpp
)

add_executable(traffic_model ${sources})

target_include_directories(traffic_model PRIVATE ${headers_dir})