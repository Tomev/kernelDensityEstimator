cmake_minimum_required(VERSION 3.11)
project(kernelDensityEstimator)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES kernels/normalKernel.cpp)

add_library(kernelDensityEstimator interfaces/i_kernel.h kernels/normalKernel.cpp kernels/normalKernel.h)
add_executable(kernelDensityEstimator_run ${SOURCES})

include_directories(kernels)

add_subdirectory(tests)

target_link_libraries(kernelDensityEstimator_run KERNELS_LIB)
