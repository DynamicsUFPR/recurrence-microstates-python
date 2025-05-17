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
import pybind11
from setuptools import setup, Extension
## ---------------------------------------------------------------------------------------------------------------------
##      - Define the extension module settings.
ext_modules = [
    Extension(
        "RMAPy",
        [
            "src/rma_py.cpp",
            "src/rma/distribution.cpp"
        ],
        include_dirs = [pybind11.get_include()],
        language = "c++"
    ),
]
## ---------------------------------------------------------------------------------------------------------------------
##      - Call the library setup.
setup(
    name = "RMAPy",
    version = "0.1.0",
    description = "A Python library for analyzing dynamical systems with recurrence microstates",
    ext_modules = ext_modules
)