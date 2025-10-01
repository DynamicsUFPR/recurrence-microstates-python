//
//                  Histogram Body
//
//  ------------------------------------------------------------------------------------------------------------------
//          Include file header:
#include "histogram.h"
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "sampling/full.h"
#include "sampling/random.h"
#include "shape/diagonal.h"
#include "shape/square.h"
#include "shape/triangle.h"
//  ------------------------------------------------------------------------------------------------------------------
Histogram::Histogram(
    const py::buffer_info &x,
    const py::buffer_info &y,
    const std::vector<int> &structure,
    const std::unique_ptr<IRecurrence> &recurrence,
    const double sampling_rate,
    const SamplingMode sampling_mode,
    const ShapeName shape_name
    ) {
    //          Initialize the shape.
    switch (shape_name) {
        case ShapeName::Square: shape = std::make_unique<Square>(x, y, structure, recurrence); break;
        case ShapeName::Diagonal: shape = std::make_unique<Diagonal>(x, y, structure, recurrence); break;
        case ShapeName::Triangle: shape = std::make_unique<Triangle>(x, y, structure, recurrence); break;
        default: throw std::invalid_argument("Unknown shape name");
    }

    //          Initialize the sampling mode.
    switch (sampling_mode) {
        case SamplingMode::Full: sampler = std::make_unique<Full>(x, y, shape, structure, sampling_rate); break;
        case SamplingMode::Random: sampler = std::make_unique<Random>(x, y, shape, structure, sampling_rate); break;
        default: throw std::runtime_error("Invalid sampling mode");
    }

}
//  ------------------------------------------------------------------------------------------------------------------
std::vector<double> Histogram::compute(const unsigned int threads) const {
    return sampler->run(threads);
}
