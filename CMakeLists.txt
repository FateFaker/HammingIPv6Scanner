cmake_minimum_required(VERSION 3.19)
project(HammingIPv6Scanner)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

#add_executable(HammingIPv6Scanner
#        cmdline.h
#        targets_generate.cpp
#        hamming.cpp)
add_executable(hamming hamming.cpp)
add_executable(targets_generate targets_generate.cpp )