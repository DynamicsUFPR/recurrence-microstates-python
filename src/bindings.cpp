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
#include "rqa/entropy.h"
//  ------------------------------------------------------------------------------------------------------------------
//          Define the Python module:
PYBIND11_MODULE(rmapy, m) {
    m.doc() = "A Python library for analyzing dynamical systems with recurrence microstates.";
    //  --------------------------------------------------------------------------------------------------------------
    //          Export sampling modes.
    py::enum_<SamplingMode>(m, "SamplingMode")
        .value("Full", SamplingMode::Full)
        .value("Random", SamplingMode::Random);
    //  --------------------------------------------------------------------------------------------------------------
    //          Export `distribution` function.
    m.def("distribution", static_cast<py::array_t<double>(*)(
            const py::array_t<double>&,
            const py::array_t<double>&,
            const py::object&,
            const std::vector<int>&,
            double,
            unsigned int,
            SamplingMode
        )>(&distribution)
        , "Compute a motif recurrence distribution.",
        py::arg("x"),
        py::arg("y"),
        py::arg("params"),
        py::arg("structure"),
        py::arg("sampling") = 0.05,
        py::arg("threads") = 0,
        py::arg("sampling_mode") = SamplingMode::Random);

    m.def("distribution",
        static_cast<py::array_t<double>(*)(
            const py::array_t<double>&,
            const py::array_t<double>&,
            const py::object&,
            const py::int_&,
            double,
            unsigned int,
            SamplingMode
        )>(&distribution),
        py::arg("x"),
        py::arg("y"),
        py::arg("params"),
        py::arg("n"),
        py::arg("sampling") = 0.05,
        py::arg("threads") = 0,
        py::arg("sampling_mode") = SamplingMode::Random
    );

    m.def("distribution",
        static_cast<py::array_t<double>(*)(
            const py::array_t<double>&,
            const py::object&,
            const py::int_&,
            double,
            unsigned int,
            SamplingMode
        )>(&distribution),
        py::arg("x"),
        py::arg("params"),
        py::arg("n"),
        py::arg("sampling") = 0.05,
        py::arg("threads") = 0,
        py::arg("sampling_mode") = SamplingMode::Random
    );
    //  --------------------------------------------------------------------------------------------------------------
    //          Export `entropy` function.
    m.def("entropy", &entropy, "Compute the recurrence microstates entropy.",
        py::arg("dist"));
}