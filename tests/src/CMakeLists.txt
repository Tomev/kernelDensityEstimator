include_directories(${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include)

add_executable(kernelsTests kernels/normalKernel_test.cpp kernels/linearKernel_test.cpp)

target_link_libraries(kernelsTests gtest gtest_main)
target_link_libraries(kernelsTests KERNELS_LIB)