//
//                  Recurrence Microstates Entropy (RME) Header
//
//  ------------------------------------------------------------------------------------------------------------------
#pragma once
//  ------------------------------------------------------------------------------------------------------------------
#ifndef RQA_ENTROPY_H
#define RQA_ENTROPY_H
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
///         Compute the recurrence entropy from a distribution.
inline py::float_ entropy(const py::array_t<double>& dist) {
    //          Prepare...
    py::float_ result = 0.0;
    const auto info = dist.request();
    const auto ptr = static_cast<double *>(info.ptr);

    for (int i = 0; i < info.shape[0]; i++) {
        const auto p = ptr[i];
        if (p > 0.0) result += static_cast<py::float_>((-1) * p * std::log2(p));
    }

    //          Return our result =3
    return result;
}
//  ------------------------------------------------------------------------------------------------------------------
#endif