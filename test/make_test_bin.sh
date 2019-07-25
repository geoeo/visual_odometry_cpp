#!/usr/bin/env bash
~/Workspace/C++/cxxtest-4.3/bin/cxxtestgen --error-printer -o runner.cpp MyTestSuite.h
g++ -o runner -I ~/Workspace/C++/cxxtest-4.3/ runner.cpp

