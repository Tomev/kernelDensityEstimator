cmake_minimum_required(VERSION 3.11)
project(kernelDensityEstimator)

set(CMAKE_CXX_STANDARD 17)

add_library(kernelDensityEstimator interfaces/i_kernel.h kernels/normalKernel.cpp kernels/normalKernel.h)