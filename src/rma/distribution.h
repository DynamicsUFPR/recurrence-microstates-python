//
//            Header for "distribution" function.
//
// --------------------------------------------------------------------------------------------------------------------
#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
// --------------------------------------------------------------------------------------------------------------------
//    - Import PyBind11
#include <pybind11/pybind11.h>
//    - Import some PyBind11 functionalities.
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
//    - Import lib-std
#include <thread>
// --------------------------------------------------------------------------------------------------------------------
#include "../cfg/enums.h"
// --------------------------------------------------------------------------------------------------------------------
namespace py = pybind11;
// --------------------------------------------------------------------------------------------------------------------
py::array_t<double> distribution(
    py::array_t<double> const &x,
    py::array_t<double> const &y,
    py::object const &params,
    std::vector<int> const &structure,
    Shape shape = Shape::Square,
    SamplingMode sampling_mode = SamplingMode::Random,
    double num_samples = 0.05,
    bool threads = std::thread::hardware_concurrency() > 1
);
// --------------------------------------------------------------------------------------------------------------------
#endif //DISTRIBUTION_H
