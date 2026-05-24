cmake_minimum_required(VERSION 3.16)

project(syrk_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(BLAS REQUIRED)

add_library(syrk_lib
    src/syrk.cpp
)

add_executable(test_syrk
    tests/test_syrk.cpp
)

target_link_libraries(test_syrk
    syrk_lib
)

add_executable(bench_syrk
    bench/bench_syrk.cpp
)

target_link_libraries(bench_syrk
    syrk_lib
    ${BLAS_LIBRARIES}
)

add_executable(all_cblas_tests
    tests/all_cblas_tests.c
)

target_link_libraries(all_cblas_tests
    ${BLAS_LIBRARIES}
)

add_executable(test_dgemm
    tests/test_dgemm.c
)

target_link_libraries(test_dgemm
    ${BLAS_LIBRARIES}
)
