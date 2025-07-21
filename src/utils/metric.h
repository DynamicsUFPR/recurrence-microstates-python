//
//                  Metric Header
//
//  ------------------------------------------------------------------------------------------------------------------
#pragma once
//  ------------------------------------------------------------------------------------------------------------------
#ifndef UTIL_METRIC_H
#define UTIL_METRIC_H
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <pybind11/pybind11.h>
#include <cmath>
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
///         Virtual class to compute a metric.
class IMetric {
public:
    virtual double evaluate(const double* x_ptr, const double* y_ptr, ssize_t shape, unsigned long stride, ssize_t x_idx, ssize_t y_idx) const = 0;
    ///         Class deconstruction.
    virtual ~IMetric() = default;
};
//  ------------------------------------------------------------------------------------------------------------------
//          Euclidean metric.
class Euclidean final : public IMetric {
public:
    [[nodiscard]] double evaluate(
          const double* x_ptr,         //    Input `x`
          const double* y_ptr,         //    Input `y`
          const ssize_t shape,          //    First dimension size
          const unsigned long stride,   //    Stride of the first dimension
          const ssize_t x_idx,          //    Pre-computed offset of `x`
          const ssize_t y_idx           //    Pre-computed offset of `y`
    ) const override {
        double value = 0.0;
        for (ssize_t i = 0; i < shape; i++) {
            const double dx = x_ptr[i * stride + x_idx] - y_ptr[i * stride + y_idx];
            value += dx * dx;
        }
        return std::sqrt(value);
    }
};
#endif