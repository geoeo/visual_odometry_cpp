cmake_minimum_required(VERSION 3.14)
project(visual_odometry)

set(CMAKE_CXX_STANDARD 17)


# all dependecies of ImageLib have to be set here as well
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# CImg
set(CIMG_H_PATH ~/Workspace/C++/CImg-2.6.7)
include_directories( ${CIMG_H_PATH} )

FIND_PACKAGE(X11)
FIND_PACKAGE(Threads REQUIRED)

link_directories(${X11_LIB_DIRS})
include_directories(${X11_INCLUDE_DIR})
SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${X11_LIBRARIES} )
# CImg end

# Sophus
set(SOPHUS_H_PATH ~/Workspace/C++/Sophus)
include_directories( ${SOPHUS_H_PATH} )

include_directories(include)
include_directories(inline)

include_directories("~/Workspace/C++/ImageLib/include")
include_directories("~/Workspace/C++/ImageLib/inline")
link_directories("~/Workspace/C++/ImageLib/cmake-build-debug")

add_executable(visual_odometry main.cpp include/io.h src/io.cpp)

target_link_libraries(visual_odometry ${llvm_libs})
target_link_libraries(visual_odometry Eigen3::Eigen)
target_link_libraries(visual_odometry ${SYSTEM_LIBS} )
target_link_libraries(visual_odometry ImageLib)
