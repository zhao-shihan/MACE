cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(MACE_PROJECT)

# ================================================================================================================================
# Variables
# ================================================================================================================================
# Dirs
set(MACE_PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(MACE_PROJECT_CMAKE_DIR ${MACE_PROJECT_ROOT_DIR}/cmake)
set(MACE_PROJECT_SRC_DIR ${MACE_PROJECT_ROOT_DIR}/source)
set(MACE_BUILDIN_YAML_CPP_DIR ${MACE_PROJECT_SRC_DIR}/external/yaml-cpp)

# ================================================================================================================================
# Options
# ================================================================================================================================
# Basic options
option(MACE_ENABLE_VIS "Build MACE with visualization" ON)
option(MACE_BUILD_TEST "Build MACE with test module" ON)
# Advance options
option(MACE_SHOW_ALL_COMPILER_WARNINGS "Do not surpress any compiler warnings, even they are raised from external dependencies." OFF)

# ================================================================================================================================
# Dependencies
# ================================================================================================================================
# MPI
find_package(MPI 3.0 REQUIRED C)
message(STATUS "MACE uses MPI_C includes from: ${MPI_C_INCLUDE_DIRS}")
message(STATUS "MACE uses MPI_C libraries: ${MPI_C_LIBRARIES}")

# Geant4
if(MACE_ENABLE_VIS)
    find_package(Geant4 11.0.0 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 11.0.0 REQUIRED)
endif()
message(STATUS "MACE uses Geant4 includes from: ${Geant4_INCLUDE_DIRS}")
message(STATUS "MACE uses Geant4 libraries: ${Geant4_LIBRARIES}")

# ROOT
find_package(ROOT 6.24.02 REQUIRED COMPONENTS Geom)
message(STATUS "MACE uses ROOT includes from: ${ROOT_INCLUDE_DIRS}")
message(STATUS "MACE uses ROOT libraries: ${ROOT_LIBRARIES}")

# EIGEN3
find_package(Eigen3 3.3.0 REQUIRED)
message(STATUS "MACE uses Eigen3 includes from: ${EIGEN3_INCLUDE_DIRS}")

# ================================================================================================================================
# MACE at C++20
# ================================================================================================================================
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
elseif(CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "MACE should be built, at least, with C++20")
endif()
message(STATUS "MACE will be compiled with C++${CMAKE_CXX_STANDARD}")

# ================================================================================================================================
# Let's go!
# ================================================================================================================================
add_subdirectory(${MACE_BUILDIN_YAML_CPP_DIR})
add_subdirectory(${MACE_PROJECT_SRC_DIR}/MACE)
if(MACE_BUILD_TEST)
    add_subdirectory(${MACE_PROJECT_SRC_DIR}/test)
endif()
