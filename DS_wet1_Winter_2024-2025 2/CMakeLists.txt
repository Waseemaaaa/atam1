cmake_minimum_required(VERSION 3.28)
project(DS_wet1_Winter_2024_2025)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DS_wet1_Winter_2024_2025
        main25a1.cpp
        plains25a1.cpp
        plains25a1.h
        wet1util.h
        Horse.h
        AVLtree.h
        Herd.h)
