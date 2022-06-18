cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
include(CMakeDependentOption)

project(MACE_PROJECT)

# ================================================================================================================================
# CMPs
# ================================================================================================================================

# enable MSVC_RUNTIME_LIBRARY target property
# see https://cmake.org/cmake/help/latest/policy/CMP0091.html
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

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
option(MACE_USE_SHARED_MSVC_RT "Select the MSVC runtime library for use (MSVC only). ON for shared (.dll), OFF for static (.lib). If you run into link error related to MSVC runtime, you can try to flip this." ON)

# Advance options
option(MACE_SHOW_ALL_COMPILE_WARNINGS "Show all compile warnings. Once turned on, MACE_SURPRESS_COMPILE_WARNINGS will be turned off, and MACE_SHOW_GCC_EFFCXX_COMPILE_WARNINGS will be turned on" OFF)
cmake_dependent_option(MACE_SURPRESS_COMPILE_WARNINGS "Surpress compile warnings raise from external dependencies." ON "NOT MACE_SHOW_ALL_COMPILE_WARNINGS" OFF)
cmake_dependent_option(MACE_SHOW_GCC_EFFCXX_COMPILE_WARNINGS "Show -Weffc++ compile warnings. (gcc only)" OFF "NOT MACE_SHOW_ALL_COMPILE_WARNINGS" ON)

# Set for MACE_USE_SHARED_MSVC_RT
if(MACE_USE_SHARED_MSVC_RT)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# ================================================================================================================================
# Dependencies
# ================================================================================================================================

# Eigen
include(${MACE_PROJECT_CMAKE_DIR}/FindEigen.cmake)
# yaml-cpp
include(${MACE_PROJECT_CMAKE_DIR}/FindOrBuildYamlCpp.cmake)
# MPI
include(${MACE_PROJECT_CMAKE_DIR}/FindMPI.cmake)
# ROOT
include(${MACE_PROJECT_CMAKE_DIR}/FindROOT.cmake)
# Geant4
include(${MACE_PROJECT_CMAKE_DIR}/FindGeant4.cmake)

# ================================================================================================================================
# Some global compiler options
# ================================================================================================================================

# Check consistency
message(STATUS "C compiler ID: ${CMAKE_C_COMPILER_ID}")
message(STATUS "C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}")
if(NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "${CMAKE_CXX_COMPILER_ID}")
    message(NOTICE "***Warning: The compiler ID of C compiler (${CMAKE_C_COMPILER_ID}) is inconsistent with that of C++ compiler (${CMAKE_CXX_COMPILER_ID}). Ignore this warning if this is expected")
endif()

# inform OpenMPI not to bring mpicxx in, it's necessary for most cases.
add_definitions(-DOMPI_SKIP_MPICXX)
# inform MPICH and derivatives not to bring mpicxx in, seems unnecessary but more consistent.
add_definitions(-DMPICH_SKIP_MPICXX)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # Enable standard-conformance
    add_definitions(/permissive- /Zc:__cplusplus /Zc:inline)
    message(STATUS "MSVC standard-conformance mode enabled")
    # Be permissive to standard cstring
    add_definitions(/D_CRT_SECURE_NO_WARNINGS)
    # See https://root-forum.cern.ch/t/preprocessor-macro-x86-64-problem-with-clhep-on-windows/50431/2
    if(${ROOT_VERSION} LESS_EQUAL 6.26.04)
        # We simply define the accidentally involved __uint128_t to a random type and pray that it won't actually be used.
        add_definitions(/D__uint128_t=float)
    endif()
endif()

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
