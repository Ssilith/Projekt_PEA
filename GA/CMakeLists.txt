cmake_minimum_required(VERSION 3.21)
project(PEA_3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(PEA_3 main.cpp cmake-build-debug/Matrix.cpp cmake-build-debug/Matrix.h cmake-build-debug/Test.cpp cmake-build-debug/Test.h cmake-build-debug/GeneticAlgorithm.cpp cmake-build-debug/GeneticAlgorithm.h)
