//
//                  Shape Header
//
//  ------------------------------------------------------------------------------------------------------------------
#pragma once
//  ------------------------------------------------------------------------------------------------------------------
#ifndef RMA_SAMPLING_H
#define RMA_SAMPLING_H
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <vector>
#include <memory>
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "shape.h"
//  ------------------------------------------------------------------------------------------------------------------
//          Sampling modes:
enum class SamplingMode { Full, Random };
//  ------------------------------------------------------------------------------------------------------------------
///         Virtual class to reference a sampling mode.
class ISampling {
protected:
    ///         Data.
    const py::buffer_info &x;
    const py::buffer_info &y;
    ///         Motif shape.
    const std::unique_ptr<IShape> &shape;
    ///         RP structure.
    std::vector<ssize_t> rp_structure;
    ///         Number of elements of a structure.
    const int structure_size;
    ///         Function to get each motif position and run the process.
    [[nodiscard]] virtual std::vector<double> task(ssize_t begin, ssize_t end) const = 0;

public:
    ///         Run
    [[nodiscard]] virtual const std::vector<double> run(unsigned int threads) const = 0;
    ///         Class construction.
    explicit ISampling(const py::buffer_info &x, const py::buffer_info &y, const std::unique_ptr<IShape> &shape, const std::vector<int> &structure);
    ///         Class deconstruction.
    virtual ~ISampling() = default;
};
//  ------------------------------------------------------------------------------------------------------------------
#endif