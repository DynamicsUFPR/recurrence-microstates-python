//
//                  Random Sampling Mode Header
//
//  ------------------------------------------------------------------------------------------------------------------
#pragma once
//  ------------------------------------------------------------------------------------------------------------------
#ifndef RMA_SAMPLING_MD_RANDOM_H
#define RMA_SAMPLING_MD_RANDOM_H
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "../sampling.h"
//  ------------------------------------------------------------------------------------------------------------------
///         Virtual class to reference a sampling mode.
class Random final : public ISampling {
    ///         Number total of motifs in an RP.
    ssize_t num_samples = 0;
    ///         Function to get each motif position and run the process. (In each thread)
    [[nodiscard]] std::vector<double> task(ssize_t begin, ssize_t end) const override;
public:
    ///         Run!
    [[nodiscard]] const std::vector<double> run(unsigned int threads) const override;
    ///         Class construction.
    explicit Random(
        const py::buffer_info &x,
        const py::buffer_info &y,
        const std::unique_ptr<IShape> &shape,
        const std::vector<int> &structure,
        double sampling_rate
        );
};
//  ------------------------------------------------------------------------------------------------------------------
#endif