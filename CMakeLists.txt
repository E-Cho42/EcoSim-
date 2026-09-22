cmake_minimum_required(VERSION 3.15)
project(ecosim)

execute_process(COMMAND python3 -m pybind11 --cmakedir OUTPUT_VARIABLE pybind11_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
find_package(pybind11 REQUIRED)

pybind11_add_module(ecosim
    cpp/functions.cpp
    cpp/grid.cpp
    cpp/herb.cpp
)