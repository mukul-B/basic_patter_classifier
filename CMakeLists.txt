cmake_minimum_required(VERSION 3.17)
project(paternRec)

set(CMAKE_CXX_STANDARD 14)

add_executable(paternRec main.cpp test.cpp test.h cmake-build-debug/problem3..cpp "cmake-build-debug/ problem2.cpp" cmake-build-debug/Metricimp.cpp MatricOP.h fileOP.h RandomNoGenerator.h DiscriminantCases.h)

#[[
find_package(Python2 COMPONENTS Development )
target_include_directories(paternRec PRIVATE ${Python2_INCLUDE_DIRS}  )
target_link_libraries(paternRec Python2::Python )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PYTHONHOME}/include)
include_directories(${PYTHONHOME}/Lib/site-packages/numpy/core/include)
link_directories(${PYTHONHOME}/libs)]]
