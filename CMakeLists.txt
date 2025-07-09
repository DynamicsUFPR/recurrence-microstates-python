cmake_minimum_required(VERSION 3.14)
project(rmapy LANGUAGES CXX)

##      We will use C++ 23+
set(CMAKE_CXX_STANDARD 23)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
    add_compile_options(-std=c++23)
endif()


##      Active the compilation mode with Python extension.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

##      Find the Python interpreter and the headers.
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

##      Download Pybind11, if necessary.
include(FetchContent)
FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG v2.11.1  # Change here to the desired version!
)
FetchContent_MakeAvailable(pybind11)

##      Add the Python Module
pybind11_add_module(rmapy
        src/rma_py.cpp
        src/rma/distribution.cpp
        src/rma/histogram.cpp
        src/rma/shape.cpp
        src/rma/shape/square.cpp
        src/rma/sampling.cpp
        src/rma/sampling/full.cpp
)

##      Include files .h
target_include_directories(rmapy PRIVATE ${CMAKE_SOURCE_DIR}/src)
