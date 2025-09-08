//
//                  Full Sampling Mode Body
//
//  ------------------------------------------------------------------------------------------------------------------
//          Include file header:
#include "full.h"
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <numeric>
#include <memory>
#include <vector>
#include <future>
#include <cmath>
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "../shape.h"
#include "../sampling.h"
//  ------------------------------------------------------------------------------------------------------------------
Full::Full(
    const py::buffer_info &x,
    const py::buffer_info &y,
    const std::unique_ptr<IShape> &shape,
    const std::vector<int> &structure,
    double _
    ) : ISampling(x, y, shape, structure) {
    //          Define the usable RP size
    const ssize_t x_dims = x.ndim - 1;
    const ssize_t y_dims = y.ndim - 1;

    if (static_cast<ssize_t>(structure.size()) != x_dims + y_dims) throw std::invalid_argument("Structure is not compatible with the input data.");
    if (x.shape[0] != y.shape[0]) throw std::invalid_argument("`x` and `y` first dimension must have same size.");

    for (ssize_t i = 0; i < x_dims; i++) {
        const ssize_t len = x.shape[i + 1] - (structure[i] - 1);
        if (len <= 0)
            throw std::invalid_argument("Structure is too large for some dimension of `x`.");

        total_motifs *= len;
        rp_structure[i] = len;
    }

    for (ssize_t i = 0; i < y_dims; i++) {
        const ssize_t len = y.shape[i + 1] - (structure[i + x_dims] - 1);
        if (len <= 0)
            throw std::invalid_argument("Structure is too large for some dimension of `y`.");

        total_motifs *= len;
        rp_structure[i + x_dims] = len;
    }
}
//  ------------------------------------------------------------------------------------------------------------------
const std::vector<double> Full::run(const unsigned int threads) const {
    //      Compute the number of "rows" that we have per thread, and the mod of this operation.
    const ssize_t int_rows = std::floor(rp_structure[0] / threads);
    ssize_t rest_rows = rp_structure[0] % threads;

    //      Call our tasks...
    ssize_t start_value = 0;
    std::vector<std::future<std::vector<double>>> tasks(threads);
    for (unsigned int i = 0; i < threads; i++) {
        const ssize_t incrementor = int_rows + (rest_rows > 0 ? 1 : 0);
        const ssize_t end_value = start_value + incrementor - 1;

        tasks[i] = std::async(std::launch::async, [this, start_value, end_value]() {
            return this->task(start_value, end_value);
        });

        start_value += incrementor;
        rest_rows--;
    }

    //      Wait result...
    auto result = tasks[0].get();
    for (ssize_t i = 1; i < threads; i++) {
        auto local_result = tasks[i].get();
        for (ssize_t p = 0; p < shape->numb_motifs(); p++)
            result[p] += local_result[p];
    }

    //      Normalize...
    for (ssize_t p = 0; p < shape->numb_motifs(); p++)
        result[p] /= total_motifs;

    return result;
}
//  ------------------------------------------------------------------------------------------------------------------
std::vector<double> Full::task(const ssize_t begin, const ssize_t end) const {

    //          Allocate memory.
    std::vector<double> result(shape->numb_motifs(), 0);

    std::vector<ssize_t> idx(structure_size, 0);
    std::vector<ssize_t> itr(structure_size, 0);
    idx[0] = begin;

    //          Number of elements.
    const ssize_t elements = ((end - begin) + 1) * std::accumulate(rp_structure.begin() + 1, rp_structure.end(), 1 ,std::multiplies());

    //          Run
    for (ssize_t i = 0; i < elements; i++) {
        result[shape->get_index(idx, itr)]++;

        idx[0]++;
        for (ssize_t k = 0; k < structure_size - 1; k++) {
            if (k == 0) {
                if (idx[k] > end) {
                    idx[k] = begin;
                    idx[k + 1]++;
                }
                else break;
                continue;
            }
            if (idx[k] >= rp_structure[k]) {
                idx[k] = 0;
                idx[k + 1]++;
            }
            else break;
        }
    }

    //          Return the result.
    return result;
}
//  ------------------------------------------------------------------------------------------------------------------
