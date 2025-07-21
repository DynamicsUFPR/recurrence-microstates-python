//
//                  Shape Header
//
//  ------------------------------------------------------------------------------------------------------------------
#pragma once
//  ------------------------------------------------------------------------------------------------------------------
#ifndef RMA_SHAPE_H
#define RMA_SHAPE_H
//  ------------------------------------------------------------------------------------------------------------------
///         Max area of a motif.
#define MAX_MOTIF_AREA 36
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <vector>
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "recurrence.h"
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
//          Shape names:
enum class ShapeName { Square, Diagonal };
//  ------------------------------------------------------------------------------------------------------------------
///         Virtual class to reference motif shapes.
class IShape {
protected:
    ///         Motif area (number of elements inside it)
    int motif_area = 0;
    ///         Motif structure.
    const std::vector<int> &structure;
    ///         Power vector.
    std::vector<int> power_vector;
    ///         Recurrence function.
    const std::unique_ptr<IRecurrence> &recurrence;
    ///         Input x.
    const double* x;
    const py::buffer_info &x_info;
    ///         Input y.
    const double* y;
    const py::buffer_info &y_info;

    ///         Data strides.
    std::vector<ssize_t> x_strides;
    std::vector<ssize_t> y_strides;

    ///         Values for first dimension (is equal!)
    ssize_t first_dim_shape;
    ssize_t first_dim_stride;
    ///         Compute the motif area.
    [[nodiscard]] virtual int compute_area() const = 0;
public:
    ///         Compute a motif decimal identifier (MDI).
    virtual auto get_index(const std::vector<ssize_t> &idx, std::vector<ssize_t> &itr) const -> const ssize_t = 0;
    ///         Get the number of motifs that can exist.
    [[nodiscard]] ssize_t numb_motifs() const;
    ///         Class construction.
    explicit IShape(const py::buffer_info &x, const py::buffer_info &y, const std::vector<int> &structure, const std::unique_ptr<IRecurrence> &recurrence);
    ///         Class deconstruction.
    virtual ~IShape() = default;
};
//  ------------------------------------------------------------------------------------------------------------------
#endif