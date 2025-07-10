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
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "../rma/distribution.h"
#include "rr.h"
//  ------------------------------------------------------------------------------------------------------------------
///         Compute the laminarity.
inline double determinism(const py::array_t<double> &x, const py::object &threshold) {
    //          Compute the distribution.
    const py::array_t<double> dist = distribution(x, threshold, 3, 0.05, 0, SamplingMode::Random, ShapeName::Diagonal);

    const py::buffer_info info = dist.request();
    const auto ptr = static_cast<double *>(info.ptr);
    //          Compute the recurrence rate.
    const double rr = rate(std::vector<double>(ptr, ptr + info.shape[0]));

    //          Compute laminarity.
    return 1 - ((1 / rr) * ptr[2]);
}
//  ------------------------------------------------------------------------------------------------------------------
#endif