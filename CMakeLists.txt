cmake_minimum_required(VERSION 3.11)
project(kernelDensityEstimator)

set(CMAKE_CXX_STANDARD 17)

add_library(kernelDensityEstimator interfaces/i_kernel.h src/kernels/normalKernel.cpp src/kernels/normalKernel.h)

include_directories(src/kernels)

add_subdirectory(tests)
add_subdirectory(src/kernels)

