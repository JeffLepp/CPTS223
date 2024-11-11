cmake_minimum_required(VERSION 3.16)
project(CPTS_223_MA4)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# Manually add the OpenMP flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fopenmp")

# Add your executable
add_executable(MA4 main.cpp)

# Ensure the linker finds OpenMP
find_package(OpenMP REQUIRED)
target_link_libraries(MA4 OpenMP::OpenMP_CXX)