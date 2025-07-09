//
//                  Full Sampling Mode Header
//
//  ------------------------------------------------------------------------------------------------------------------
#pragma once
//  ------------------------------------------------------------------------------------------------------------------
#ifndef RMA_SAMPLING_MD_FULL_H
#define RMA_SAMPLING_MD_FULL_H
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <vector>
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "../sampling.h"
//  ------------------------------------------------------------------------------------------------------------------
///         Virtual class to reference a sampling mode.
class Full final : public ISampling {
    ///         Number total of motifs in an RP.
    ssize_t total_motifs = 1;
    ///         Function to get each motif position and run the process. (In each thread)
    std::vector<double> task(ssize_t begin, ssize_t end) const override;
public:
    ///         Run!
    const std::vector<double> run(unsigned int threads) const override;
    ///         Class construction.
    explicit Full(const py::buffer_info &x, const py::buffer_info &y, const std::unique_ptr<IShape> &shape, const std::vector<int> &structure);
};
//  ------------------------------------------------------------------------------------------------------------------
#endif