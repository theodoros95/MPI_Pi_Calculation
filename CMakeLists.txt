cmake_minimum_required(VERSION 3.14)
project(test2 C)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

set(CMAKE_C_STANDARD 11)

add_executable(test2 main.c)
