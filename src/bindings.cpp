//
//                  Main C++ File
//
//      By:
//          - Gabriel V. Ferreira (UFPR 2025, Project RMAPy)
//  ------------------------------------------------------------------------------------------------------------------
//          Import necessary libraries:
#include <pybind11/pybind11.h>
namespace py = pybind11;
//  ------------------------------------------------------------------------------------------------------------------
//          Library files:
#include "rma/distribution.h"
#include "rma/sampling.h"
#include "rma/shape.h"
#include "rma/recurrence.h"
#include "rqa/rr.h"
#include "rqa/lam.h"
#include "rqa/det.h"
#include "rqa/entropy.h"
#include "rqa/disorder.h"
#include "utils/distances.h"
//  ------------------------------------------------------------------------------------------------------------------
//          Define the Python module:
PYBIND11_MODULE(recurrence_microstates, m) {
    m.doc() = "A Python library for analyzing dynamical systems with recurrence microstates.";
    //  --------------------------------------------------------------------------------------------------------------
    //          Export sampling modes.
    py::enum_<SamplingMode>(m, "SamplingMode")
        .value("Full", SamplingMode::Full)
        .value("Random", SamplingMode::Random);
    //  --------------------------------------------------------------------------------------------------------------
    //          Export shapes.
    py::enum_<ShapeName>(m, "Shape")
        .value("Square", ShapeName::Square)
        .value("Diagonal", ShapeName::Diagonal)
        .value("Triangle", ShapeName::Triangle);
    //  --------------------------------------------------------------------------------------------------------------
    //          Export recurrence functions.
    py::enum_<RecurrenceFunction>(m, "Recurrence")
        .value("Standard", RecurrenceFunction::Standard)
        .value("Corridor", RecurrenceFunction::Corridor)
        .value("JRP", RecurrenceFunction::JRP);
    //  --------------------------------------------------------------------------------------------------------------
    //          Export `distribution` function.
    m.def("distribution", static_cast<py::array_t<double>(*)(
            const py::array_t<double>&,
            const py::array_t<double>&,
            const py::object&,
            const std::vector<int>&,
            double,
            unsigned int,
            SamplingMode,
            ShapeName,
            RecurrenceFunction
        )>(&distribution)
        , "Compute a motif recurrence distribution.",
        py::arg("x"),
        py::arg("y"),
        py::arg("params"),
        py::arg("structure"),
        py::arg("sampling") = 0.05,
        py::arg("threads") = 0,
        py::arg("sampling_mode") = SamplingMode::Random,
        py::arg("shape") = ShapeName::Square,
        py::arg("recurrence") = RecurrenceFunction::Standard
        );

    m.def("distribution",
        static_cast<py::array_t<double>(*)(
            const py::array_t<double>&,
            const py::array_t<double>&,
            const py::object&,
            const py::int_&,
            double,
            unsigned int,
            SamplingMode,
            ShapeName,
            RecurrenceFunction
        )>(&distribution),
        py::arg("x"),
        py::arg("y"),
        py::arg("params"),
        py::arg("n"),
        py::arg("sampling") = 0.05,
        py::arg("threads") = 0,
        py::arg("sampling_mode") = SamplingMode::Random,
        py::arg("shape") = ShapeName::Square,
        py::arg("recurrence") = RecurrenceFunction::Standard
    );

    m.def("distribution",
        static_cast<py::array_t<double>(*)(
            const py::array_t<double>&,
            const py::object&,
            const py::int_&,
            double,
            unsigned int,
            SamplingMode,
            ShapeName,
            RecurrenceFunction
        )>(&distribution),
        py::arg("x"),
        py::arg("params"),
        py::arg("n"),
        py::arg("sampling") = 0.05,
        py::arg("threads") = 0,
        py::arg("sampling_mode") = SamplingMode::Random,
        py::arg("shape") = ShapeName::Square,
        py::arg("recurrence") = RecurrenceFunction::Standard
    );
    //  --------------------------------------------------------------------------------------------------------------
    //          Export `entropy` function.
    m.def("entropy", &entropy, "Compute the recurrence microstates entropy.", py::arg("dist"));
    //  --------------------------------------------------------------------------------------------------------------
    //          Export `rate` function.
    m.def("recurrence_rate", &recurrence_rate, "Estimate the recurrence rate.", py::arg("dist"));
    //  --------------------------------------------------------------------------------------------------------------
    //          Export `laminarity` function.
    m.def("laminarity", &laminarity, "Estimate the laminarity", py::arg("x"), py::arg("threshold"), py::arg("threads") = 0);
    //  --------------------------------------------------------------------------------------------------------------
    //          Export `determinism` function.
    m.def("determinism", &determinism, "Estimate the determinism", py::arg("x"), py::arg("threshold"), py::arg("threads") = 0);
    //  --------------------------------------------------------------------------------------------------------------
    //          Export `disorder` function.
    m.def("disorder", &disorder, "Compute the disorder quantifier", py::arg("x"), py::arg("threshold"), py::arg("n"), py::arg("threshold_range") = 0.2, py::arg("segment_size") = 10);
    //  --------------------------------------------------------------------------------------------------------------
    //          Export `distances` function.
    m.def("distances", &distances, py::arg("x"), py::arg("y"));
}