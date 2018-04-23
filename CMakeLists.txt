# CMakeLists.txt
cmake_minimum_required(VERSION 2.8)
project(nn-cuda-cr)

# set( CUDA_TOOLKIT_ROOT_DIR "/Developer/NVIDIA/CUDA-9.1/")
find_package(CUDA QUIET REQUIRED)

set( CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set( ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set( SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


set(SOURCE
   ${SRC_DIR}/main.cpp
   ${SRC_DIR}/cpu_computing.cpp
   ${SRC_DIR}/cuda_computing.cu
)

set(INCLUDE_DIRS
   ${CMAKE_CURRENT_SOURCE_DIR}/include
)

IF (WIN32)
ELSE()
  set( CMAKE_CXX_FLAGS "-g -W -Wall -std=c++17")
ENDIF()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

set(CUDA_NVCC_FLAGS "-Wno-deprecated-gpu-targets --expt-relaxed-constexpr --resource-usage")

include_directories( ${INCLUDE_DIRS})
link_directories(${LINK_DIRS})

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
cuda_add_executable(main ${SOURCE} )
set_target_properties(main PROPERTIES COMPILE_FLAGS "-DDEVICE_COMPILE")
 