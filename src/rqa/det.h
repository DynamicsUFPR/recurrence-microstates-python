//
//                  Determinism (DET) Header
//
//  ------------------------------------------------------------------------------------------------------------------
#pragma once
//  ------------------------------------------------------------------------------------------------------------------
#ifndef RQA_DET_H
#define RQA_DET_H
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "../rma/distribution.h"
#include "rr.h"
//  ------------------------------------------------------------------------------------------------------------------
///         Compute the determinism.
inline double determinism(const py::array_t<double> &x, const py::object &threshold, const unsigned int threads = 0) {
    //          Compute the distribution.
    const py::array_t<double> dist = distribution(x, threshold, 3, 0.05, threads, SamplingMode::Random, ShapeName::Diagonal);
    const py::buffer_info info = dist.request();
    const auto ptr = static_cast<double *>(info.ptr);

    if (info.shape[0] < 3) {
        throw std::runtime_error("distribution() result too short: expected at least 3 values.");
    }

    const double prob = ptr[2];

    if (std::isnan(prob)) {
        throw std::runtime_error("ptr[2] is NaN.");
    }

    if (std::isinf(prob)) {
        throw std::runtime_error("ptr[2] is infinite.");
    }

    if (prob < 0.0 || prob > 1.0) {
        throw std::runtime_error("ptr[2] is out of bounds: " + std::to_string(prob));
    }

    //          Compute the recurrence rate.
    const double rr = recurrence_rate(std::vector(ptr, ptr + info.shape[0]));
    //          Prepare to computed DET.
    const double rr_usable = rr + 1e-12;
    const double value = prob / rr_usable;

    if (std::isnan(value) || std::isinf(value)) {
        return 0.0;
    }

    //          Compute determinism.
    return 1 - value;
}
//  ------------------------------------------------------------------------------------------------------------------
#endif