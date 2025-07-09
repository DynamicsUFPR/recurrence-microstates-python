//
//                  Shape Body
//
//  ------------------------------------------------------------------------------------------------------------------
//          Include file header:
#include "shape.h"
//  ------------------------------------------------------------------------------------------------------------------
IShape::IShape(
    const py::buffer_info &x,
    const py::buffer_info &y,
    const std::vector<int> &structure,
    const std::unique_ptr<IRecurrence> &recurrence
    ) :
structure(structure),
recurrence(recurrence),
x(static_cast<double*>(x.ptr)),
x_info(x),
y(static_cast<double*>(y.ptr)),
y_info(y) {
    first_dim_shape = x_info.shape[0];
    first_dim_stride = x_info.strides[0];
}
//  ------------------------------------------------------------------------------------------------------------------
ssize_t IShape::numb_motifs() const {
    //          Verify if the motif area is valid.
    if (motif_area > MAX_MOTIF_AREA) throw std::runtime_error("Motif's area exceeds the maximum allowed value");
    if (motif_area <= 0) throw std::runtime_error("Motif's area is not positive");

    //          Compute 2^\sigma.
    const double pow_result = std::pow(motif_area, 2);
    if (pow_result < 0.0) throw std::runtime_error("Motif's area is negative");
    if (pow_result > static_cast<double>(std::numeric_limits<int>::max())) throw std::runtime_error("Motif's area is too large");

    //          Return the number of available motifs.
    return static_cast<ssize_t>(pow_result);
}
