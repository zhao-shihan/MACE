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
option(MACE_ENABLE_VIS "Build MACE with visualization." ON)
option(MACE_BUILDIN_YAML_CPP "Use build-in yaml-cpp." OFF)
option(MACE_BUILD_TEST "Build MACE with test programs." ON)

# Advance options
option(MACE_SURPRESS_COMPILE_WARNINGS "Surpress compile warnings raise from external dependencies." ON)
option(MACE_SHOW_EFFCXX_COMPILE_WARNINGS "Show -Weffc++ compile warnings. (gcc only)" OFF)
option(MACE_SHOW_ALL_COMPILE_WARNINGS "Show all compile warnings. Once turned on, MACE_SURPRESS_COMPILE_WARNINGS will be turned off, and MACE_SHOW_EFFCXX_COMPILE_WARNINGS will be turned on" OFF)

# Option relationships
if(MACE_SHOW_ALL_COMPILE_WARNINGS)
    set(MACE_SURPRESS_COMPILE_WARNINGS OFF)
    set(MACE_SHOW_EFFCXX_COMPILE_WARNINGS ON)
endif()

# ================================================================================================================================
# Dependencies
# ================================================================================================================================

# MPI
find_package(MPI 2.2 REQUIRED C)
message(STATUS "MACE uses MPI_C includes from: ${MPI_C_INCLUDE_DIRS}")
message(STATUS "MACE uses MPI_C libraries: ${MPI_C_LIBRARIES}")
add_definitions(-DOMPI_SKIP_MPICXX) # inform OpenMPI not to bring mpicxx in, it's necessary for most cases.
add_definitions(-DMPICH_SKIP_MPICXX) # inform MPICH/IntelMPI not to bring mpicxx in, seems unnecessary but more consistent.

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
find_package(Eigen3 3.0.0 REQUIRED)
message(STATUS "MACE uses Eigen3 includes from: ${EIGEN3_INCLUDE_DIRS}")

# yaml-cpp
if(NOT MACE_BUILDIN_YAML_CPP)
    find_package(yaml-cpp 0.6.0 QUIET)
    if(NOT yaml-cpp_FOUND)
        message("Notice: yaml-cpp not found. Turning on MACE_BUILDIN_YAML_CPP.")
        set(MACE_BUILDIN_YAML_CPP ON)
        set(YAML_CPP_INCLUDE_DIR ${MACE_BUILDIN_YAML_CPP_DIR}/include)
        set(YAML_CPP_LIBRARIES yaml-cpp)
    endif()
endif()
message(STATUS "MACE uses yaml-cpp includes from: ${YAML_CPP_INCLUDE_DIR}")
message(STATUS "MACE uses yaml-cpp libraries: ${YAML_CPP_LIBRARIES}")

# ================================================================================================================================
# MACE build type
# ================================================================================================================================

if(CMAKE_CONFIGURATION_TYPES)
    message(STATUS "MACE build type: ${CMAKE_CONFIGURATION_TYPES}")
else()
    if(NOT CMAKE_BUILD_TYPE)
        # Default to "release"
        set(CMAKE_BUILD_TYPE "Release")
    endif()
    message(STATUS "MACE build type: ${CMAKE_BUILD_TYPE}")
endif()

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

# Build-in yaml-cpp
if(MACE_BUILDIN_YAML_CPP)
    add_subdirectory(${MACE_BUILDIN_YAML_CPP_DIR})
endif()

# MACE
add_subdirectory(${MACE_PROJECT_SRC_DIR}/MACE)

# Test
if(MACE_BUILD_TEST)
    add_subdirectory(${MACE_PROJECT_SRC_DIR}/test)
endif()
