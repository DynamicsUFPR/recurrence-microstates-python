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
//  ------------------------------------------------------------------------------------------------------------------
//          Define the Python module:
PYBIND11_MODULE(rmapy, m) {
    m.doc() = "A Python library for analyzing dynamical systems with recurrence microstates.";
    //  --------------------------------------------------------------------------------------------------------------
    //          Export `distribution` function.
    m.def("distribution", &distribution, "Compute a motif recurrence distribution.",
        py::arg("x"),
        py::arg("y"),
        py::arg("params"),
        py::arg("structure"),
        py::arg("sampling") = 0.05,
        py::arg("threads") = 0);
}