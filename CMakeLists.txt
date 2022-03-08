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
# About compile warnings
# ================================================================================================================================
# More warnings
add_definitions(-Wall -Wextra)
# Suppress external warnings:
#
# TStorage.h:133:12: warning: compound assignment with ‘volatile’-qualified left operand is deprecated [-Wvolatile]
#   133 |       bits |= kIsOnHeap;
#       |       ~~~~~^~~~~~~~~~~~
# TStorage.h:135:12: warning: compound assignment with ‘volatile’-qualified left operand is deprecated [-Wvolatile]
#   135 |       bits &= ~kIsOnHeap;
#       |       ~~~~~^~~~~~~~~~~~~
#
add_definitions(-Wno-volatile)
if(CMAKE_COMPILER_IS_GNUCXX)
    if(GCC_VERSION GREATER_EQUAL 11)
        #
        # PlainObjectBase.h:905:102: warning: bitwise operation between different enumeration types ‘Eigen::PlainObjectBase<Eigen::Matrix<double, 3, 1> >::<unnamed enum>’ and ‘Eigen::StorageOptions’ is deprecated [-Wdeprecated-enum-enum-conversion]
        #   905 |       EIGEN_STATIC_ASSERT((EIGEN_IMPLIES(MaxRowsAtCompileTime==1 && MaxColsAtCompileTime!=1, (Options&RowMajor)==RowMajor)
        #       |                                                                                              ~~~~~~~~^~~~~~~~~~
        # util/StaticAssert.h:33:54: note: in definition of macro ‘EIGEN_STATIC_ASSERT’
        #    33 |     #define EIGEN_STATIC_ASSERT(X,MSG) static_assert(X,#MSG);
        #       |                                                      ^
        # PlainObjectBase.h:905:28: note: in expansion of macro ‘EIGEN_IMPLIES’
        #   905 |       EIGEN_STATIC_ASSERT((EIGEN_IMPLIES(MaxRowsAtCompileTime==1 && MaxColsAtCompileTime!=1, (Options&RowMajor)==RowMajor)
        #       |                            ^~~~~~~~~~~~~
        # PlainObjectBase.h:906:102: warning: bitwise operation between different enumeration types ‘Eigen::PlainObjectBase<Eigen::Matrix<double, 3, 1> >::<unnamed enum>’ and ‘Eigen::StorageOptions’ is deprecated [-Wdeprecated-enum-enum-conversion]
        #   906 |                         && EIGEN_IMPLIES(MaxColsAtCompileTime==1 && MaxRowsAtCompileTime!=1, (Options&RowMajor)==0)
        #       |                                                                                              ~~~~~~~~^~~~~~~~~~
        # util/StaticAssert.h:33:54: note: in definition of macro ‘EIGEN_STATIC_ASSERT’
        #    33 |     #define EIGEN_STATIC_ASSERT(X,MSG) static_assert(X,#MSG);
        #       |                                                      ^
        # PlainObjectBase.h:906:28: note: in expansion of macro ‘EIGEN_IMPLIES’
        #   906 |                         && EIGEN_IMPLIES(MaxColsAtCompileTime==1 && MaxRowsAtCompileTime!=1, (Options&RowMajor)==0)
        #       |                            ^~~~~~~~~~~~~
        #
        # ...
        #
        add_definitions(-Wno-deprecated-enum-enum-conversion)
    endif()
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
# Global includes
# ================================================================================================================================
# external
include_directories(${MPI_CXX_INCLUDE_DIRS})
include_directories(${Geant4_INCLUDE_DIRS})
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIRS})
# built-in
include_directories(${MACE_THIRD_PARTY_DIR}/G4mpi/include)
# intrinsic
include_directories(${MACE_PROJECT_ROOT_DIR}/Core)
include_directories(${MACE_PROJECT_ROOT_DIR}/Utility)

# ================================================================================================================================
# sub directories
# ================================================================================================================================
add_subdirectory(Core)
add_subdirectory(Reconstruction)
add_subdirectory(Simulation)
add_subdirectory(ThirdParty)
add_subdirectory(Utility)
