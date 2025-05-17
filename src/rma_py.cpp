//
//            Main C++ File
//
// --------------------------------------------------------------------------------------------------------------------
//    - Import PyBind11
#include <pybind11/pybind11.h>
//    - Import some PyBind11 functionalities.
#include <pybind11/numpy.h>
//    - Import from lib-std
#include <thread>
// --------------------------------------------------------------------------------------------------------------------
//    - Library headers
#include "cfg/enums.h"
#include "rma/distribution.h"
// --------------------------------------------------------------------------------------------------------------------
namespace py = pybind11;
// --------------------------------------------------------------------------------------------------------------------
//    - Create our modules.
PYBIND11_MODULE(RMAPy, m) {
//        1. Export ENUMs to configuration.
//    a) Motif Shape
    py::enum_<Shape>(m, "Shape")
        .value("Square", Shape::Square)
        .export_values();

//    b) Library Sampling Mode
    py::enum_<SamplingMode>(m, "SamplingMode")
        .value("Random", SamplingMode::Random)
        .value("Full", SamplingMode::Full)
        .export_values();

//        2. Export the distribution function to compute the recurrence distributions.
    m.def("distribution", &distribution,
          py::arg("x"), py::arg("y"), py::arg("params"), py::arg("structure"),
          py::arg("shape") = Shape::Square,
          py::arg("sampling_mode") = SamplingMode::Random,
          py::arg("num_samples") = 0.05,
          py::arg("threads") = std::thread::hardware_concurrency() > 1
    );
}