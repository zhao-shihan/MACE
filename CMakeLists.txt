cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# enable MSVC_RUNTIME_LIBRARY target property, see https://cmake.org/cmake/help/latest/policy/CMP0091.html
cmake_policy(SET CMP0091 NEW)

include(CMakeDependentOption)

project(MACE_PROJECT)

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

# Basic
# Options (ON/OFF)
option(MACE_BUILD_TEST "Build MACE with test programs." ON)
option(MACE_BUILTIN_EIGEN "Use built-in Eigen (network or pre-downloaded source is required)." OFF)
option(MACE_BUILTIN_G4GDML "Use built-in and G4gdml. This option will be automatically turned ON if Geant4::G4gdml is not found. It is unrecommended to manually turn ON this switch, leave it be unless you know what you are doing." OFF)
option(MACE_BUILTIN_XERCES_C "Use built-in Xerces-C++ (network or pre-downloaded source is required). This option is ignored if need not to build built-in G4gdml." OFF)
option(MACE_BUILTIN_YAML_CPP "Use built-in yaml-cpp (network or pre-downloaded source is required)." OFF)
option(MACE_ENABLE_VIS "Build MACE with visualization. Note that whether Geant4 supports visualization is determined by the options when Geant4 is built. MACE does not, and cannot, affect whether G4 enables visualization." ON)
option(MACE_USE_STATIC_G4 "Attempt to link Geant4 static libraries if available, by finding the \"static\" component of G4. There may be some performance gains if successful (depending on the compiler options), but MACE needs to be recompiled to use the new G4 if the G4 library is upgraded or replaced. If cannot find \"static\", dynamic libraries will be linked." ON)

# Advance
# Options (ON/OFF)
option(MACE_SHOW_ALL_COMPILE_WARNINGS "Show all compile warnings. Once turned on, MACE_SURPRESS_COMPILE_WARNINGS will be turned off, and MACE_SHOW_GCC_EFFCXX_COMPILE_WARNINGS will be turned on" OFF)
option(MACE_USE_SHARED_MSVC_RT "Select the MSVC runtime library for use (MSVC only). ON for shared (.dll), OFF for static (.lib). If you run into link error related to MSVC runtime, you can try to flip this." ON)
cmake_dependent_option(MACE_SHOW_GCC_EFFCXX_COMPILE_WARNINGS "Show -Weffc++ compile warnings. (gcc only)" OFF "NOT MACE_SHOW_ALL_COMPILE_WARNINGS" ON)
cmake_dependent_option(MACE_SURPRESS_COMPILE_WARNINGS "Surpress compile warnings raise from external dependencies." ON "NOT MACE_SHOW_ALL_COMPILE_WARNINGS" OFF)
set(MACE_BUILTIN_EIGEN_VERSION 3.4.0 CACHE STRING "Set built-in Eigen version (if required).")
set(MACE_BUILTIN_YAML_CPP_VERSION 0.7.0 CACHE STRING "Set built-in yaml-cpp version (if required).")

# =============================================================================
# Global compile options
# =============================================================================

include(${MACE_PROJECT_CMAKE_DIR}/GlobalCompileOptions.cmake)

# =============================================================================
# Dependencies
# =============================================================================

# MPI
include(${MACE_PROJECT_CMAKE_DIR}/LookForMPI.cmake)
# ROOT
include(${MACE_PROJECT_CMAKE_DIR}/LookForROOT.cmake)
# Geant4
include(${MACE_PROJECT_CMAKE_DIR}/LookForGeant4.cmake)
# Eigen
include(${MACE_PROJECT_CMAKE_DIR}/LookForEigen.cmake)
# yaml-cpp
include(${MACE_PROJECT_CMAKE_DIR}/LookForYamlCpp.cmake)

# =============================================================================
# Let's go!
# =============================================================================

# Config for MACE
include(${MACE_PROJECT_CMAKE_DIR}/MACECompileOptions.cmake)
include(${MACE_PROJECT_CMAKE_DIR}/IncludeDirectories.cmake)

# MACE
add_subdirectory("${MACE_PROJECT_SRC_DIR}/MACE")

# Test
if(MACE_BUILD_TEST)
    add_subdirectory("${MACE_PROJECT_SRC_DIR}/test")
endif()
