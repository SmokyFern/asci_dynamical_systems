cmake_minimum_required(VERSION 3.22.2)

project(asci_lorenz LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pthread")

find_package(Eigen3 3.3 REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
)

add_library(dyn_sys STATIC src/dynamical_systems.cpp)
add_library(integrators STATIC src/integrators.cpp)
add_library(meshgrid STATIC src/mesh_generator.cpp)
add_library(asci_plotter STATIC src/asci_plotter.cpp)

add_executable(test src/test.cpp)
add_executable(asci_lorenz src/asci_lorenz.cpp)
target_link_libraries(asci_lorenz PRIVATE Eigen3::Eigen 
                                          dyn_sys 
                                          integrators
                                          meshgrid
                                          asci_plotter)