cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(MACE)

# ================================================================================================================================
# Variables
# ================================================================================================================================
# Dirs
set(MACE_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(MACE_CMAKE_DIR ${MACE_ROOT_DIR}/cmake)
set(MACE_SOURCE_DIR ${MACE_ROOT_DIR}/source)
set(MACE_EXTERNAL_DIR ${MACE_SOURCE_DIR}/external)
set(MACE_TEST_DIR ${MACE_SOURCE_DIR}/test)

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
find_package(MPI 3.0 REQUIRED)
message(STATUS "MACE uses MPI_C includes from: ${MPI_C_INCLUDE_DIRS}")
message(STATUS "MACE uses MPI_C libraries: ${MPI_C_LIBRARIES}")
message(STATUS "MACE uses MPI_CXX includes from: ${MPI_CXX_INCLUDE_DIRS}")
message(STATUS "MACE uses MPI_CXX libraries: ${MPI_CXX_LIBRARIES}")

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
# About compile warnings
# ================================================================================================================================
# More warnings
add_definitions(-Wall -Wextra)
# Surpress those from external
if(NOT MACE_SHOW_ALL_COMPILER_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        # Open MPI
        add_definitions(-Wno-cast-function-type)
        # ROOT
        add_definitions(-Wno-volatile)
        if(GCC_VERSION GREATER_EQUAL 11)
            # Eigen3
            add_definitions(-Wno-deprecated-enum-enum-conversion)
        endif()
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        # ROOT
        add_definitions(-Wno-deprecated-volatile)
        # Eigen3
        add_definitions(-Wno-deprecated-anon-enum-enum-conversion)
    endif()
endif()

add_subdirectory(${MACE_SOURCE_DIR})
