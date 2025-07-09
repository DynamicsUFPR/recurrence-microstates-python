//
//                  Histogram Body
//
//  ------------------------------------------------------------------------------------------------------------------
//          Include file header:
#include "histogram.h"
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "sampling/full.h"
#include "shape/square.h"
//  ------------------------------------------------------------------------------------------------------------------
Histogram::Histogram(const py::buffer_info &x, const py::buffer_info &y, const std::vector<int> &structure, const std::unique_ptr<IRecurrence> &recurrence) {
    //          Initialize the shape.
    shape = std::make_unique<Square>(x, y, structure, recurrence);
    //          Initialize the sampling mode.
    sampler = std::make_unique<Full>(x, y, shape, structure);
}
//  ------------------------------------------------------------------------------------------------------------------
std::vector<double> Histogram::compute(const unsigned int threads) const {
    return sampler->run(threads);
}
