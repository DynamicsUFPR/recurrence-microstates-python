//
//                  Square Shape Header
//
//  ------------------------------------------------------------------------------------------------------------------
#pragma once
//  ------------------------------------------------------------------------------------------------------------------
#ifndef RMA_SHAPE_FT_SQUARE_H
#define RMA_SHAPE_FT_SQUARE_H
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include<pybind11/pybind11.h>
#include<pybind11/numpy.h>
#include<pybind11/stl.h>
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
//          Necessary library files:
#include "../shape.h"
//  ------------------------------------------------------------------------------------------------------------------
///         Virtual class to reference a sampling mode.
class Square final : public IShape {
    ///         Compute the motif area.
    int compute_area() const override;
public:
    ///         Compute a motif decimal identifier (MDI).
    const ssize_t get_index(const std::vector<ssize_t> &idx, std::vector<ssize_t> &itr) const override;
    ///         Class construction.
    explicit Square(const py::buffer_info &x, const py::buffer_info &y, const std::vector<int> &structure, const std::unique_ptr<IRecurrence> &recurrence);
};
//  ------------------------------------------------------------------------------------------------------------------
#endif