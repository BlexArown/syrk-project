cmake_minimum_required(VERSION 3.10)
project(lab_syrk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(BLAS REQUIRED)

add_library(syrk_lib src/syrk.cpp)

add_executable(main_app src/main.cpp)
target_link_libraries(main_app syrk_lib)

add_executable(test_syrk tests/test_syrk.cpp)
target_link_libraries(test_syrk syrk_lib)

add_executable(bench_syrk bench/bench_syrk.cpp)
target_link_libraries(bench_syrk syrk_lib ${BLAS_LIBRARIES})
