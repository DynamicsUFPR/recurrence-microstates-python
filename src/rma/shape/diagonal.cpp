//
//                  Square Shape Body
//
//  ------------------------------------------------------------------------------------------------------------------
//          Include file header:
#include "diagonal.h"
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "../shape.h"
//  ------------------------------------------------------------------------------------------------------------------
Diagonal::Diagonal(
    const py::buffer_info &x,
    const py::buffer_info &y,
    const std::vector<int> &structure,
    const std::unique_ptr<IRecurrence> &recurrence
    ): IShape(x, y, structure, recurrence) {
    //          Compute the motif area.
    motif_area = compute_area();
    //          Build our power vector.
    power_vector = std::vector(motif_area, 1);
    for (int i = 0; i < motif_area; i++) {
        power_vector[i] = static_cast<int>(std::pow(2, i));
    }
}
//  ------------------------------------------------------------------------------------------------------------------
int Diagonal::compute_area() const {
    return structure[0];
}
//  ------------------------------------------------------------------------------------------------------------------
const ssize_t Diagonal::get_index(const std::vector<ssize_t> &idx, std::vector<ssize_t> &itr) const {
    ssize_t index = 0;
    //          Copy values from idx to itr.
    std::copy(idx.begin(), idx.end(), itr.begin());

    //          Iterate...
    for (const int m : power_vector) {
        ssize_t x_idx = 0;
        ssize_t y_idx = 0;

        for (ssize_t i = 1; i < x_info.ndim; i++) {
            x_idx += itr[i - 1] * x_strides[i - 1];
        }

        for (ssize_t i = 1; i < y_info.ndim; i++) {
            y_idx += itr[(i - 1) + (x_info.ndim - 1)] * y_strides[i - 1];
        }

        if (recurrence->compute(x, y, first_dim_shape, first_dim_stride, x_idx, y_idx))
            index += m;

        for (unsigned long k = 0; k < structure.size(); k++) {
            itr[k] += 1;
        }
    }

    return index;
}
