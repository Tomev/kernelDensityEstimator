include_directories(${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include)

add_executable(KDETests kernels/normalKernel_test.cpp)

target_link_libraries(KDETests gtest gtest_main)
target_link_libraries(KDETests KERNELS_LIB)