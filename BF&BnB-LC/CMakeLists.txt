cmake_minimum_required(VERSION 3.21)
project(PEA)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(PEA main.cpp cmake-build-debug/Test.cpp cmake-build-debug/Test.h cmake-build-debug/BruteForce.cpp cmake-build-debug/BruteForce.h cmake-build-debug/Matrix.cpp cmake-build-debug/Matrix.h cmake-build-debug/Time.cpp cmake-build-debug/Time.h cmake-build-debug/BranchAndBound.cpp cmake-build-debug/BranchAndBound.h)
