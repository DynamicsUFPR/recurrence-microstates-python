##
##                  RMAPy: A Python library for analyzing dynamical systems with recurrence microstates
##          By Gabriel Vinicius Ferreira (UFPR 2025)
##          Contributions:
##              - Felipe Eduardo Lopes da Cruz
##          Advisors:
##              - Thiago de Lima Prado
##              - Sérgio Roberto Lopes
## ---------------------------------------------------------------------------------------------------------------------
##          GitHub repository: https://github.com/DynamicsUFPR/RMAPy
## ---------------------------------------------------------------------------------------------------------------------
##          This lib uses PyBind11 as a binding library between Python and C++.
## ---------------------------------------------------------------------------------------------------------------------
##              How Install and Compile
##      To install the necessary libraries and compile the RMAPy, just run:
##
##          pip install pybind11 setuptools
##          pip install .
## ---------------------------------------------------------------------------------------------------------------------
##      - Import the necessary python libraries to compile the project.
import sys

import pybind11
from setuptools import setup, Extension
## ---------------------------------------------------------------------------------------------------------------------
##      - Define the compiler (necessary when using Window)
compiler = None
if sys.platform == "win32":
    compiler = "mingw32"
## ---------------------------------------------------------------------------------------------------------------------
##      - Define the extension module settings.
ext_modules = [
    Extension(
        "recurrence_microstates",
        [
            "src/bindings.cpp",
            "src/rma/distribution.cpp",
            "src/rma/histogram.cpp",
            "src/rma/shape.cpp",
            "src/rma/shape/square.cpp",
            "src/rma/shape/diagonal.cpp",
            "src/rma/sampling.cpp",
            "src/rma/sampling/full.cpp",
            "src/rma/sampling/random.cpp"
        ],
        include_dirs = [pybind11.get_include()],
        language = "c++",
        extra_compile_args = ["-std=c++23"],
    ),
]
## ---------------------------------------------------------------------------------------------------------------------
##      - Call the library setup.
setup(
    name = "rmapy",
    version = "0.1.0",
    description = "A Python library for analyzing dynamical systems with recurrence microstates",
    ext_modules = ext_modules,
    zip_safe = False,
    options = {"build": {"compiler": compiler}} if compiler else {},
)