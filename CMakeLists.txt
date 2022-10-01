cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Enable MSVC_RUNTIME_LIBRARY target property, see https://cmake.org/cmake/help/latest/policy/CMP0091.html
cmake_policy(SET CMP0091 NEW)
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    # ExternalProject_Add sets the timestamps of extracted contents to the time of extraction, see https://cmake.org/cmake/help/latest/policy/CMP0135.html
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
set(MACE_PROJECT_SRC_DIR "${MACE_PROJECT_ROOT_DIR}/source")
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
option(MACE_BUILTIN_EIGEN "Use built-in Eigen (network or pre-downloaded source is required)." OFF)
option(MACE_BUILTIN_MSGSL "Use built-in Microsoft.GSL (network or pre-downloaded source is required)." OFF)
option(MACE_BUILTIN_YAML_CPP "Use built-in yaml-cpp (network or pre-downloaded source is required)." OFF)
option(MACE_SIGNAL_HANDLER "Build with signal handling. Signal handlers are registered at the construction of environment." ON)
option(MACE_USE_G4GDML "Build with G4gdml support. This option will be automatically turned OFF if Geant4::G4gdml is not found. Once turned off, you are not able to export geometry (to ROOT or other)." ON)
option(MACE_USE_G4VIS "Build Geant4 applications of MACE with available visualization. Note that whether Geant4 supports visualization is determined by options with which Geant4 is built. MACE does not, and cannot, affect whether G4 enables visualization." ON)
option(MACE_USE_STATIC_G4 "Attempt to link Geant4 static libraries if available, by finding the \"static\" component of G4. There may be some performance gains if successful (depending on the compiler options), but some other (originally) possible dynamic linkages becomes impossible. If cannot find \"static\", dynamic libraries will be linked." ON)

# Advance
# Options (ON/OFF)
option(MACE_ENABLE_MSVC_STD_CONFORMITY "Build MACE with standard-conformity (MSVC only: /permissive- /Zc:__cplusplus /Zc:inline)." ON)
option(MACE_SHOW_ALL_COMPILE_WARNINGS "Show all compile warnings. Once turned on, MACE_SURPRESS_COMPILE_WARNINGS will be turned off, and MACE_SHOW_GCC_EFFCXX_COMPILE_WARNINGS will be turned on." OFF)
option(MACE_USE_SHARED_MSVC_RT "Select the MSVC runtime library for use (MSVC only). ON for shared (.dll), OFF for static (.lib). If you run into link error related to MSVC runtime, you can try to flip this." ON)
cmake_dependent_option(MACE_SHOW_GCC_EFFCXX_COMPILE_WARNINGS "Show -Weffc++ compile warnings. (GCC only)" OFF "NOT MACE_SHOW_ALL_COMPILE_WARNINGS" ON)
cmake_dependent_option(MACE_SURPRESS_COMPILE_WARNINGS "Surpress compile warnings raise from external dependencies." ON "NOT MACE_SHOW_ALL_COMPILE_WARNINGS" OFF)
set(MACE_BUILTIN_ARGPARSE_VERSION 2.6 CACHE STRING "Set built-in argparse version (if required).")
set(MACE_BUILTIN_BACKWARD_VERSION 1.6 CACHE STRING "Set built-in backward-cpp version (if required).")
set(MACE_BUILTIN_EIGEN_VERSION 3.4.0 CACHE STRING "Set built-in Eigen version (if required).")
set(MACE_BUILTIN_MSGSL_VERSION 4.0.0 CACHE STRING "Set built-in Microsoft.GSL version (if required).")
set(MACE_BUILTIN_YAML_CPP_VERSION 0.7.0 CACHE STRING "Set built-in yaml-cpp version (if required).")

# =============================================================================
# Global compile options
# =============================================================================

include(${MACE_PROJECT_CMAKE_DIR}/GlobalCompileOptions.cmake)

# =============================================================================
# Dependencies
# =============================================================================

# Required:
# MPI
include(${MACE_PROJECT_CMAKE_DIR}/LookForMPI.cmake)
# ROOT
include(${MACE_PROJECT_CMAKE_DIR}/LookForROOT.cmake)
# Geant4
include(${MACE_PROJECT_CMAKE_DIR}/LookForGeant4.cmake)

# Required, built-in if not found:
# argparse
include(${MACE_PROJECT_CMAKE_DIR}/LookForArgparse.cmake)
# backward-cpp
include(${MACE_PROJECT_CMAKE_DIR}/LookForBackward.cmake)
# Microsoft.GSL
include(${MACE_PROJECT_CMAKE_DIR}/LookForMicrosoftGSL.cmake)
# yaml-cpp
include(${MACE_PROJECT_CMAKE_DIR}/LookForYamlCpp.cmake)
# Eigen (should be the last otherwise might run into problem if other download steps raise error)
include(${MACE_PROJECT_CMAKE_DIR}/LookForEigen.cmake)

# =============================================================================
# Let's go!
# =============================================================================

add_subdirectory(${MACE_PROJECT_SRC_DIR})
