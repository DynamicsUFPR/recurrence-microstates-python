//
//                  Distribution Body
//
//  ------------------------------------------------------------------------------------------------------------------
//          Include file header:
#include "distribution.h"
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <thread>
#include <vector>
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "histogram.h"
#include "recurrence.h"
#include "../utils/metric.h"
//  ------------------------------------------------------------------------------------------------------------------
pybind11::array_t<double> distribution(
    py::array_t<double> const &x,
    py::array_t<double> const &y,
    py::object const &params,
    std::vector<int> const &structure,
    double sampling,
    unsigned int threads
) {
    //  --------------------------------------------------------------------------------------------------------------
    //          Check the input format.
    //      Here we just check if the input is a Vector or a Matrix/Array,
    //  so if it's a vector we convert it to a matrix 1xN.
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
    //  --------------------------------------------------------------------------------------------------------------
    //          Get array information.
    const auto x_info = x_checked.request();
    const auto y_info = y_checked.request();
    //  --------------------------------------------------------------------------------------------------------------
    //          Define the number of threads to use (if necessary)
    if (threads == 0) threads = std::thread::hardware_concurrency();
    if (threads == 0) throw std::runtime_error("It was not possible to determine the number of available threads. Please define it manually.");
    //  --------------------------------------------------------------------------------------------------------------
    //          Define the metric.
    const std::unique_ptr<IMetric> metric_interface = std::make_unique<Euclidean>();
    //  --------------------------------------------------------------------------------------------------------------
    //          Define the recurrence function.
    const std::unique_ptr<IRecurrence> recurrence_interface = std::make_unique<StandardRecurrence>(metric_interface, params);
    //  --------------------------------------------------------------------------------------------------------------
    //          Define a histogram architecture.
    const auto histogram = std::make_unique<Histogram>(x_info, y_info, structure, recurrence_interface);

    //          Compute the histogram.
    const auto result = histogram->compute(threads);
    return py::array_t(result.size(), result.data());
}