cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(MACE)

# ================================================================================================================================
# MACE at C++20
# ================================================================================================================================
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
elseif(CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "MACE should be built, at least, with C++20")
endif()
message(STATUS "MACE is building with C++${CMAKE_CXX_STANDARD}")

# ================================================================================================================================
# Compile flags
# ================================================================================================================================
# More warnings
add_definitions(-Wall -Wextra)
# Suppress warning from TStorage.h which is only raised in C++20 and above:
if(CMAKE_CXX_STANDARD GREATER 17)
    #
    # TStorage.h:133:12: warning: compound assignment with ‘volatile’-qualified left operand is deprecated [-Wvolatile]
    #   133 |       bits |= kIsOnHeap;
    #       |       ~~~~~^~~~~~~~~~~~
    # TStorage.h:135:12: warning: compound assignment with ‘volatile’-qualified left operand is deprecated [-Wvolatile]
    #   135 |       bits &= ~kIsOnHeap;
    #       |       ~~~~~^~~~~~~~~~~~~
    #
    add_definitions(-Wno-volatile)
endif()

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
# ?? not very sure about this if
#option(MACE_WITH_VIS "Build MACE with visualization" ON)
#if(MACE_WITH_VIS)
find_package(Geant4 11.0.0 REQUIRED ui_all vis_all)
#else()
#    find_package(Geant4 11.0.0 REQUIRED)
#endif()
message(STATUS "MACE uses Geant4 includes from: ${Geant4_INCLUDE_DIRS}")
message(STATUS "MACE uses Geant4 libraries: ${Geant4_LIBRARIES}")

# ROOT
find_package(ROOT 6.24.02 REQUIRED COMPONENTS Geom)
message(STATUS "MACE uses ROOT includes from: ${ROOT_INCLUDE_DIRS}")
message(STATUS "MACE uses ROOT libraries: ${ROOT_LIBRARIES}")

# EIGEN3
find_package(Eigen3 3.3.9 REQUIRED)
message(STATUS "MACE uses Eigen3 includes from: ${EIGEN3_INCLUDE_DIRS}")

# ================================================================================================================================
# Variables
# ================================================================================================================================
# Dirs
set(MACE_PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(MACE_THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/ThirdParty)

# ================================================================================================================================
# sub directories
# ================================================================================================================================
add_subdirectory(Core)
add_subdirectory(Reconstruction)
add_subdirectory(Simulation)
add_subdirectory(ThirdParty)
add_subdirectory(Utility)
