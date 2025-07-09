//
//                  Square Shape Body
//
//  ------------------------------------------------------------------------------------------------------------------
//          Include file header:
#include "square.h"
#include <iostream>
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "../shape.h"
//  ------------------------------------------------------------------------------------------------------------------
Square::Square(
    const py::buffer_info &x,
    const py::buffer_info &y,
    const std::vector<int> &structure,
    const std::unique_ptr<IRecurrence> &recurrence
    ): IShape(x, y, structure, recurrence) {
    //          Compute the motif area.
    motif_area = compute_area();
    //          Build our power vector.
    power_vector = std::vector<int>(motif_area, 1);
    for (int i = 0; i < motif_area; i++) {
        power_vector[i] = std::pow(2, i);
    }
}
//  ------------------------------------------------------------------------------------------------------------------
int Square::compute_area() const {
    return std::accumulate(structure.begin(), structure.end(), 1, std::multiplies());
}
//  ------------------------------------------------------------------------------------------------------------------
const ssize_t Square::get_index(const std::vector<ssize_t> &idx, std::vector<ssize_t> &itr) const {
    ssize_t index = 0;

    //          Copy values from idx to itr.
    std::ranges::copy(idx, itr.begin());

    //          Iterate...
    for (ssize_t m = 0; m < power_vector.size(); m++) {
        ssize_t x_idx = 0;
        ssize_t y_idx = 0;

        for (ssize_t i = 1; i < x_info.ndim; i++) {
            x_idx += itr[i - 1] * x_info.strides[i];
        }

        for (ssize_t i = 1; i < y_info.ndim; i++) {
            y_idx += itr[(i - 2) + y_info.ndim] * y_info.strides[i];
        }

        if (recurrence->compute(x, y, first_dim_shape, first_dim_stride, x_idx, y_idx))
            index += power_vector[m];

        itr[0]++;
        for (ssize_t k = 0; k < structure.size() - 1; k++) {
            if (itr[k] >= idx[k] + structure[k]) {
                itr[k] = idx[k];
                itr[k + 1]++;
            } else break;
        }
    }

    return index;
}
