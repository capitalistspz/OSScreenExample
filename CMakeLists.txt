cmake_minimum_required(VERSION 3.28)
project(osscreen_example)

set(CMAKE_CXX_STANDARD 20)

add_executable(osscreen_example main.cpp)

wut_create_rpx(osscreen_example)
