//
//            Code for "distribution" function.
//
// --------------------------------------------------------------------------------------------------------------------
//    - Import file header
#include "distribution.h"
// --------------------------------------------------------------------------------------------------------------------
//    - Import PyBind11
#include <pybind11/pybind11.h>
//    - Import some PyBind11 functionalities.
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
//    - Import from std-lib.
#include <vector>
#include <iostream>
// --------------------------------------------------------------------------------------------------------------------
#include "../cfg/enums.h"
// --------------------------------------------------------------------------------------------------------------------
namespace py = pybind11;
// --------------------------------------------------------------------------------------------------------------------
py::array_t<double> distribution(py::array_t<double> const &x, py::array_t<double> const &y, py::object const &params, std::vector<int> const &structure,
    Shape shape, SamplingMode sampling_mode, double num_samples, bool threads)
{
    //          Check the input format.
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

    //          Get array information.
    const py::buffer_info x_info = x_checked.request();
    const py::buffer_info y_info = y_checked.request();

    const auto x_dims = x_info.ndim - 1;
    const auto y_dims = y_info.ndim - 1;

    //          !! It is necessary that x_dims + y_dims = length(structure) !!
    if (structure.size() != (x_dims + y_dims))
        throw std::invalid_argument("The data is not compatible with the given structure.");

    //          Compute the size of all recurrence space.
    unsigned long total_motifs = 1;
    std::vector<long> space_size(x_dims + y_dims);

    for (auto i = 0; i < x_dims; i++) {
        const auto len = x_info.shape[i + 1] - (structure[i] - 1);
        if (len <= 0)
            throw std::invalid_argument("Structure is too large for dimension of x.");

        total_motifs *= len;
        space_size[i] = len;
    }

    for (auto i = 0; i < y_dims; i++) {
        const auto len = y_info.shape[i + 1] - (structure[x_dims + i] - 1);
        if (len <= 0)
            throw std::invalid_argument("Structure is too large for dimension of y.");

        total_motifs *= len;
        space_size[x_dims + i] = len;
    }

    //          Prepare the number of samples that we will be using.
    if (num_samples <= 0 || num_samples > 1)
        throw std::invalid_argument("The number of samples must be in the range (0, 1].");

    long samples = 0;
    if (sampling_mode == SamplingMode::Columnwise) samples = static_cast<long>(round(static_cast<double>(space_size[2]) * num_samples * structure[1]));
    else samples = static_cast<long>(round(static_cast<double>(static_cast<double>(total_motifs) * num_samples)));

    //          Call the method to compute the histogram and return it.
    if (shape == Shape::Square) {
        if (sampling_mode == SamplingMode::Random) {
            return py::array_t<double>{};
        }
        if (sampling_mode == SamplingMode::Full) {
            return py::array_t<double>{};
        }
        throw std::invalid_argument("Invalid sampling mode.");
    }
    if (shape == Shape::Triangle) throw std::invalid_argument("The shape Triangle is not available.");
    if (shape == Shape::Pair) throw std::invalid_argument("The shape Pair is not available.");
    if (shape == Shape::Line) throw std::invalid_argument("The shape Line is not available.");
    if (shape == Shape::Diagonal) throw std::invalid_argument("The shape Diagonal is not available.");
    throw std::invalid_argument("The library is not compatible with the given shape.");
}