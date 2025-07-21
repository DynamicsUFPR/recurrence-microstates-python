//
//                  Distances Header
//
//  ------------------------------------------------------------------------------------------------------------------
#pragma once
//  ------------------------------------------------------------------------------------------------------------------
#ifndef UTIL_DISTANCES_H
#define UTIL_DISTANCES_H
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cmath>
namespace py = pybind11;

#include "metric.h"
//  ------------------------------------------------------------------------------------------------------------------
///        Compute a distance matriz.
inline py::array_t<double> distances(const py::array_t<double> &x, const py::array_t<double> &y) {
    //      Check the input format.
    const auto x_checked = [&]() {
        if (const py::buffer_info info = x.request(); info.ndim == 1) {
            const ssize_t N = info.shape[0];
            py::array_t<double> result({static_cast<ssize_t>(1), N});
            std::memcpy(result.mutable_data(), info.ptr, sizeof(double) * N);
            return result;
        }
        return x;
    }();

    const auto y_checked = [&]() {
        if (const py::buffer_info info = y.request(); info.ndim == 1) {
            const ssize_t N = info.shape[0];
            py::array_t<double> result({static_cast<ssize_t>(1), N});
            std::memcpy(result.mutable_data(), info.ptr, sizeof(double) * N);
            return result;
        }
        return y;
    }();

    //      Get info buffer.
    const auto x_info = x_checked.request();
    const auto y_info = y_checked.request();

    //      Initialize the matriz.
    py::array_t<double> matrix({x_info.shape[1], y_info.shape[1]});
    auto info = matrix.request();
    auto ptr = static_cast<double *>(info.ptr);

    //      Compute each distance.
    auto x_ptr = static_cast<const double*>(x_info.ptr);
    auto y_ptr = static_cast<const double*>(y_info.ptr);

    const auto stride_row = static_cast<ssize_t>(info.strides[0] / sizeof(double));
    const auto stride_col = static_cast<ssize_t>(info.strides[1] / sizeof(double));


    auto metric = Euclidean();

    for (ssize_t i = 0; i < x_info.shape[1]; i++) {
        for (ssize_t j = 0; j < y_info.shape[1]; j++) {
            ptr[i * stride_row + j * stride_col] = metric.evaluate(x_ptr, y_ptr, x_info.shape[0], x_info.strides[0] / sizeof(double), i, j);
        }
    }

    return matrix;
}
#endif