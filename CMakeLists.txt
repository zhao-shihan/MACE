cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Enable MSVC_RUNTIME_LIBRARY target property
# See https://cmake.org/cmake/help/latest/policy/CMP0091.html
cmake_policy(SET CMP0091 NEW)
# Set CMP0077 to new in order to configure options for build-in libraries
# See https://discourse.cmake.org/t/what-is-the-correct-way-to-set-options-of-a-project-before-fetch-content/268/6
# See also https://cmake.org/cmake/help/latest/policy/CMP0077.html
cmake_policy(SET CMP0077 NEW)
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    # ExternalProject_Add sets the timestamps of extracted contents to the time of extraction
    # See https://cmake.org/cmake/help/latest/policy/CMP0135.html
    cmake_policy(SET CMP0135 NEW)
endif()

project(MACE VERSION 0.0.0
             LANGUAGES C CXX)

# =============================================================================
# Variables
# =============================================================================

# Dirs
set(MACE_PROJECT_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(MACE_PROJECT_CMAKE_DIR "${MACE_PROJECT_ROOT_DIR}/cmake")
set(MACE_PROJECT_SRC_DIR "${MACE_PROJECT_ROOT_DIR}/src")
set(MACE_PROJECT_3RDPARTY_DIR "${MACE_PROJECT_ROOT_DIR}/thirdparty")

# =============================================================================
# Options
# =============================================================================

include(CMakeDependentOption)

# Basic
# Options (ON/OFF)
option(MACE_BUILD_TEST "Build MACE with test programs." ON)
option(MACE_BUILTIN_ARGPARSE "Use built-in argparse (network or pre-downloaded source is required)." OFF)
option(MACE_BUILTIN_BACKWARD "Use built-in backward-cpp (network or pre-downloaded source is required)." OFF)
option(MACE_BUILTIN_FMT "Use built-in fmt (network or pre-downloaded source is required)." OFF)
option(MACE_BUILTIN_GENFIT "Use built-in GenFit (network or pre-downloaded source is required)." OFF)
option(MACE_BUILTIN_GENFIT_EVENT_DISPLAY "Build GenFit event display module if GenFit is built-in." ON)
option(MACE_BUILTIN_MSGSL "Use built-in Microsoft.GSL (network or pre-downloaded source is required)." OFF)
option(MACE_BUILTIN_PMP "Use built-in pmp (network or pre-downloaded source is required)." OFF)
option(MACE_BUILTIN_YAML_CPP "Use built-in yaml-cpp (network or pre-downloaded source is required)." OFF)
option(MACE_SIGNAL_HANDLER "Build with signal handling. Signal handlers are registered at the construction of environment." ON)
option(MACE_USE_G4VIS "Build Geant4 applications of MACE with available visualization. Note that whether Geant4 supports visualization is determined by options with which Geant4 is built. MACE does not, and cannot, affect whether G4 enables visualization." ON)
option(MACE_USE_STATIC_G4 "Attempt to link Geant4 static libraries if available, by finding the \"static\" component of G4. If \"static\" is not found, dynamic libraries will be linked." ON)

# Advance
# Options (ON/OFF)
option(MACE_ENABLE_ASAN_IN_DEBUG_BUILD "Enable AddressSanitizer in debug build" OFF)
option(MACE_ENABLE_IPO "Bulid MACE with interprocedural optimization" ON)
option(MACE_ENABLE_MSVC_STD_CONFORMITY "Build MACE with standard-conformity (MSVC only: /permissive- /Zc:__cplusplus /Zc:inline)." ON)
option(MACE_ENABLE_UBSAN_IN_DEBUG_BUILD "Enable UndefinedBehaviorSanitizer in debug build" ON)
option(MACE_FULL_UNITY_BUILD "Building MACE use unity build technique COMPLETELY." OFF)
option(MACE_SHOW_EVEN_MORE_COMPILER_WARNINGS "Add compiler flag to show even more compiler warnings (GCC: -Weffc++, Clang: -Weverything, MSVC: /Wall)." OFF)
option(MACE_USE_SHARED_MSVC_RT "Select the MSVC runtime library for use (MSVC only). ON for shared (.dll), OFF for static (.lib). If you run into link error related to MSVC runtime, you can try flip this." ON)
cmake_dependent_option(MACE_ENABLE_UNITY_BUILD "Build MACE with unity build technique." OFF "NOT MACE_FULL_UNITY_BUILD" ON)
cmake_dependent_option(MACE_SHOW_MORE_COMPILER_WARNINGS "Show compiler warnings raise from external dependencies." OFF "NOT MACE_SHOW_EVEN_MORE_COMPILER_WARNINGS" ON)
set(MACE_BUILTIN_ARGPARSE_VERSION 3.0 CACHE STRING "Set built-in argparse version (if required).")
set(MACE_BUILTIN_BACKWARD_VERSION 1.6 CACHE STRING "Set built-in backward-cpp version (if required).")
set(MACE_BUILTIN_FMT_VERSION 10.2.1 CACHE STRING "Set built-in fmt version (if required).")
set(MACE_BUILTIN_MSGSL_VERSION 4.0.0 CACHE STRING "Set built-in Microsoft.GSL version (if required).")
set(MACE_BUILTIN_PMP_VERSION 3.0.0 CACHE STRING "Set built-in fmt version (if required).")
set(MACE_BUILTIN_YAML_CPP_VERSION 0.8.0 CACHE STRING "Set built-in yaml-cpp version (if required).")

# =============================================================================
# Global compile options
# =============================================================================

include(${MACE_PROJECT_CMAKE_DIR}/GlobalCompileConfig.cmake)

# =============================================================================
# Dependencies
# =============================================================================

# Required:

# MPI
include(${MACE_PROJECT_CMAKE_DIR}/LookForMPI.cmake)
# Eigen
include(${MACE_PROJECT_CMAKE_DIR}/LookForEigen.cmake)
# Geant4
include(${MACE_PROJECT_CMAKE_DIR}/LookForGeant4.cmake)
# ROOT
include(${MACE_PROJECT_CMAKE_DIR}/LookForROOT.cmake)

# Required, built-in if not found:

# argparse
include(${MACE_PROJECT_CMAKE_DIR}/LookForArgparse.cmake)
# backward-cpp
include(${MACE_PROJECT_CMAKE_DIR}/LookForBackward.cmake)
# fmt
include(${MACE_PROJECT_CMAKE_DIR}/LookForFmt.cmake)
# GenFit
include(${MACE_PROJECT_CMAKE_DIR}/LookForGenFit.cmake)
# Microsoft.GSL
include(${MACE_PROJECT_CMAKE_DIR}/LookForMicrosoftGSL.cmake)
# PMP
include(${MACE_PROJECT_CMAKE_DIR}/LookForPMP.cmake)
# yaml-cpp
include(${MACE_PROJECT_CMAKE_DIR}/LookForYamlCpp.cmake)

# =============================================================================
# Let's go!
# =============================================================================

# Config for MACE
include(${MACE_PROJECT_CMAKE_DIR}/MACECompileConfig.cmake)
# main content
add_subdirectory(${MACE_PROJECT_SRC_DIR})
