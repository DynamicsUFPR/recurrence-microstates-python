//
//                  Sampling Body
//
//  ------------------------------------------------------------------------------------------------------------------
//          Include file header:
#include "sampling.h"
//  ------------------------------------------------------------------------------------------------------------------
ISampling::ISampling(const py::buffer_info &x, const py::buffer_info &y, const std::unique_ptr<IShape> &shape,
                     const std::vector<int> &structure) : x(x), y(y), shape(shape), rp_structure(structure.size(), 0),
                     structure_size(static_cast<int>(structure.size())) {
}
//  ------------------------------------------------------------------------------------------------------------------