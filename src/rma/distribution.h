//
//                  Distribution Header
//
//  ------------------------------------------------------------------------------------------------------------------
#pragma once
//  ------------------------------------------------------------------------------------------------------------------
#ifndef RMA_DISTRIBUTION_H
#define RMA_DISTRIBUTION_H
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <vector>

#include "sampling.h"
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
///     Compute a recurrence motif distribution.
pybind11::array_t<double> distribution(
    py::array_t<double> const &x,
    py::array_t<double> const &y,
    py::object const &params,
    std::vector<int> const &structure,
    double sampling = 0.05,
    unsigned int threads = 0,
    SamplingMode sampling_mode = SamplingMode::Random
);
//  ------------------------------------------------------------------------------------------------------------------
///     Compute a recurrence motif distribution.
pybind11::array_t<double> distribution(
    py::array_t<double> const &x,
    py::array_t<double> const &y,
    py::object const &params,
    const py::int_ &n,
    double sampling = 0.05,
    unsigned int threads = 0,
    SamplingMode sampling_mode = SamplingMode::Random
);
//  ------------------------------------------------------------------------------------------------------------------
///     Compute a recurrence motif distribution.
pybind11::array_t<double> distribution(
    py::array_t<double> const &x,
    py::object const &params,
    const py::int_ &n,
    double sampling = 0.05,
    unsigned int threads = 0,
    SamplingMode sampling_mode = SamplingMode::Random
);
//  ------------------------------------------------------------------------------------------------------------------
#endif