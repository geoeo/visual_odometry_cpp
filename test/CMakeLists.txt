cmake_minimum_required(VERSION 3.14)
project(visual_odometry_test)

set(CMAKE_CXX_STANDARD 17)

include_directories(~/Workspace/C++/cxxtest-4.3)

add_executable(visual_odometry_test main.cpp MyTestSuite.h)