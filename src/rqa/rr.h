//
//                  Recurrence Rate (RR) Header
//
//  ------------------------------------------------------------------------------------------------------------------
#pragma once
//  ------------------------------------------------------------------------------------------------------------------
#ifndef RQA_RR_H
#define RQA_RR_H
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
///         Compute the local recurrence.
inline double local_rr(ssize_t n, const ssize_t hv) {
    ssize_t sum_bits = 0;
    while (n > 0) {
        sum_bits += n & 1;      //  Sum 1 if the low bit is 1.
        n >>= 1;                //  Move n 1 bit to right.
    }

    return static_cast<double>(sum_bits) / static_cast<double>(hv);
}
//  ------------------------------------------------------------------------------------------------------------------
///         Compute the recurrence entropy from a distribution.
inline double recurrence_rate(const std::vector<double>& dist) {
    //          Prepare...
    double result = 0.0;
    //          Get "area" of a "motif structure" (idk how write it in english >.<)
    const auto area = static_cast<ssize_t>(std::floor(log2(dist.size())));
    //          Compute...
    for (int i = 0; i < dist.size(); ++i) {
        const double rr_i = local_rr(i, area);
        result += rr_i * dist[i];
    }
    //          Return our result =3
    return result;
}
//  ------------------------------------------------------------------------------------------------------------------
#endif