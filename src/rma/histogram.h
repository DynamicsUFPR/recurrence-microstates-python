//
//                  Histogram Header
//
//  ------------------------------------------------------------------------------------------------------------------
#pragma once
//  ------------------------------------------------------------------------------------------------------------------
#ifndef RMA_HISTOGRAM_H
#define RMA_HISTOGRAM_H
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
#include "sampling.h"
#include "recurrence.h"
//  ------------------------------------------------------------------------------------------------------------------
///         Object in charge of build a histogram and return it.
class Histogram final {
    ///         Sampling mode.
    std::unique_ptr<ISampling> sampler;
    ///         Motif shape.
    std::unique_ptr<IShape> shape;
public:
    ///         Compute the distribution.
    std::vector<double> compute(unsigned int threads) const;
    ///         Class constructor.
    explicit Histogram(
        const py::buffer_info &x,
        const py::buffer_info &y,
        const std::vector<int> &structure,
        const std::unique_ptr<IRecurrence> &recurrence,
        double sampling_rate,
        SamplingMode sampling_mode,
        ShapeName shape_name
        );
    ///         Class deconstruction.
    ~Histogram() = default;
};
//  ------------------------------------------------------------------------------------------------------------------
#endif