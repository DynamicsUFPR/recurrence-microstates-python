//
//                  Square Shape Body
//
//  ------------------------------------------------------------------------------------------------------------------
//          Include file header:
#include "triangle.h"
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "../shape.h"
//  ------------------------------------------------------------------------------------------------------------------
Triangle::Triangle(
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
        power_vector[i] = static_cast<int>(std::pow(2, i));
    }
}
//  ------------------------------------------------------------------------------------------------------------------
int Triangle::compute_area() const {
    int area = 0;

    for (int j = 0; j < structure[1]; j++) {
        for (int i = j; i < structure[0]; i++) {
            area += 1;
        }
    }

    return area;
}
//  ------------------------------------------------------------------------------------------------------------------
const ssize_t Triangle::get_index(const std::vector<ssize_t> &idx, std::vector<ssize_t> &itr) const {
    ssize_t index = 0;
    //          Copy values from idx to itr.
    std::copy(idx.begin(), idx.end(), itr.begin());

    //          Iterate...
    int m = 0;
    for (int j = 0; j < structure[1]; j++) {
        itr[1] = idx[1] + j;
        for (int i = j; i < structure[0]; i++) {
            itr[0] = idx[0] + i;

            ssize_t x_idx = 0;
            ssize_t y_idx = 0;

            for (ssize_t i = 1; i < x_info.ndim; i++) {
                x_idx += itr[i - 1] * x_strides[i - 1];
            }

            for (ssize_t i = 1; i < y_info.ndim; i++) {
                y_idx += itr[(i - 1) + (x_info.ndim - 1)] * y_strides[i - 1];
            }

            if (recurrence->compute(x, y, first_dim_shape, first_dim_stride, x_idx, y_idx))
                index += power_vector[m];

            m++;
        }
    }

    return index;
}
