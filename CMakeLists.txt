cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# enable MSVC_RUNTIME_LIBRARY target property, see https://cmake.org/cmake/help/latest/policy/CMP0091.html
cmake_policy(SET CMP0091 NEW)

include(CMakeDependentOption)

project(MACE_PROJECT)

# ================================================================================================================================
# Variables
# ================================================================================================================================

# Dirs
set(MACE_PROJECT_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(MACE_PROJECT_CMAKE_DIR "${MACE_PROJECT_ROOT_DIR}/cmake")
set(MACE_PROJECT_SRC_DIR "${MACE_PROJECT_ROOT_DIR}/source")
set(MACE_PROJECT_3RDPARTY_DIR "${MACE_PROJECT_ROOT_DIR}/thirdparty")

# ================================================================================================================================
# Options
# ================================================================================================================================

# Basic
# Options (ON/OFF)
option(MACE_BUILD_TEST "Build MACE with test programs." ON)
option(MACE_BUILTIN_EIGEN "Use built-in Eigen (pre-downloaded source or network required)" OFF)
option(MACE_BUILTIN_YAML_CPP "Use built-in yaml-cpp." OFF)
option(MACE_ENABLE_VIS "Build MACE with visualization. Note that whether Geant4 supports visualization is determined by the options when Geant4 is built. MACE does not, and cannot, affect whether G4 enables visualization." ON)
option(MACE_USE_STATIC_G4 "Attempt to link Geant4 static libraries if available, by finding the \"static\" component of G4. There may be some performance gains if successful (depending on the compiler options), but MACE needs to be recompiled to use the new G4 if the G4 library is upgraded or replaced. If cannot find \"static\", dynamic libraries will be linked." ON)

# Advance
# Options (ON/OFF)
option(MACE_BUILTIN_G4GDML "Use built-in Xerces-C++ and G4gdml. This option will be automatically turned ON if Geant4::G4gdml is not found. It is strongly unrecommended to manually turn ON this switch, leave it be unless you know what you are doing." OFF)
option(MACE_SHOW_ALL_COMPILE_WARNINGS "Show all compile warnings. Once turned on, MACE_SURPRESS_COMPILE_WARNINGS will be turned off, and MACE_SHOW_GCC_EFFCXX_COMPILE_WARNINGS will be turned on" OFF)
option(MACE_USE_SHARED_MSVC_RT "Select the MSVC runtime library for use (MSVC only). ON for shared (.dll), OFF for static (.lib). If you run into link error related to MSVC runtime, you can try to flip this." ON)
cmake_dependent_option(MACE_SHOW_GCC_EFFCXX_COMPILE_WARNINGS "Show -Weffc++ compile warnings. (gcc only)" OFF "NOT MACE_SHOW_ALL_COMPILE_WARNINGS" ON)
cmake_dependent_option(MACE_SURPRESS_COMPILE_WARNINGS "Surpress compile warnings raise from external dependencies." ON "NOT MACE_SHOW_ALL_COMPILE_WARNINGS" OFF)
set(MACE_DOWNLOAD_EIGEN_VERSION 3.4.0 CACHE STRING "Set Eigen version to be downloaded (if necessary).")
set(MACE_DOWNLOAD_YAML_CPP_VERSION 0.7.0 CACHE STRING "Set yaml-cpp version to be downloaded (if necessary).")

# ================================================================================================================================
# MACE at C++20
# ================================================================================================================================

set(CMAKE_CXX_STANDARD_REQUIRED ON)
if("${CMAKE_CXX_STANDARD}" STREQUAL "")
    set(CMAKE_CXX_STANDARD 20)
elseif(CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "MACE should be built, at least, with C++20")
endif()
message(STATUS "MACE will be compiled with C++${CMAKE_CXX_STANDARD}")

# ================================================================================================================================
# MACE build type
# ================================================================================================================================

if(DEFINED CMAKE_CONFIGURATION_TYPES)
    # multi-config generator
    message(STATUS "Using multi-config generator \"${CMAKE_GENERATOR}\"")
    message(STATUS "It provides the following build types: ${CMAKE_CONFIGURATION_TYPES}")
    if(DEFINED CMAKE_BUILD_TYPE)
        message(NOTICE "***Notice: Detected that CMAKE_BUILD_TYPE is defined while using the multi-config generator \"${CMAKE_GENERATOR}\".")
        message(NOTICE "           When using a multi-config generator, CMAKE_BUILD_TYPE is ignored and the build type should be specified at build time")
    endif()
else()
    # single-config generator
    message(STATUS "Using single-config generator \"${CMAKE_GENERATOR}\"")
    if(NOT DEFINED CMAKE_BUILD_TYPE)
        # Default to "Release"
        set(CMAKE_BUILD_TYPE "Release")
    endif()
    message(STATUS "MACE build type: ${CMAKE_BUILD_TYPE}")
endif()

# ================================================================================================================================
# Select MSVC runtime library
# ================================================================================================================================

# Respect to MACE_USE_SHARED_MSVC_RT
if(MACE_USE_SHARED_MSVC_RT)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# ================================================================================================================================
# Dependencies
# ================================================================================================================================

# MPI
include(${MACE_PROJECT_CMAKE_DIR}/LookForMPI.cmake)
# ROOT
include(${MACE_PROJECT_CMAKE_DIR}/LookForROOT.cmake)
# Eigen
include(${MACE_PROJECT_CMAKE_DIR}/LookForEigen.cmake)
# yaml-cpp
include(${MACE_PROJECT_CMAKE_DIR}/LookForYamlCpp.cmake)
# Geant4
include(${MACE_PROJECT_CMAKE_DIR}/LookForGeant4.cmake)

# ================================================================================================================================
# Some global compiler options
# ================================================================================================================================

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
    if(${ROOT_VERSION} VERSION_LESS_EQUAL 6.26.04)
        # We simply define the accidentally involved __uint128_t to a random type and pray that it won't actually be used.
        add_definitions(/D__uint128_t=float)
    endif()
endif()

# ================================================================================================================================
# Let's go!
# ================================================================================================================================

# MACE
add_subdirectory(${MACE_PROJECT_SRC_DIR}/MACE)

# Test
if(MACE_BUILD_TEST)
    add_subdirectory(${MACE_PROJECT_SRC_DIR}/test)
endif()
