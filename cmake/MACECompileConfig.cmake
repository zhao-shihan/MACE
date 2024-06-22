# This file is included after "find_package"s and "LookFor"s.

# =============================================================================
# MACE at C++20
# =============================================================================

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard.")
if(CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "MACE should be built, at least, with C++20")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "MACE will be compiled with C++${CMAKE_CXX_STANDARD}")

# =============================================================================
# By default, no C++ extensions available for MACE
# =============================================================================

if(NOT DEFINED CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# =============================================================================
# Unity build for MACE
# =============================================================================

if(MACE_ENABLE_UNITY_BUILD)
    set(CMAKE_UNITY_BUILD ON)
    if(MACE_FULL_UNITY_BUILD)
        set(CMAKE_UNITY_BUILD_BATCH_SIZE 0)
    else()
        set(CMAKE_UNITY_BUILD_BATCH_SIZE 8)
    endif()
    if(CMAKE_UNITY_BUILD_BATCH_SIZE GREATER 0)
        message(STATUS "Unity build enabled for MACE (batch size: ${CMAKE_UNITY_BUILD_BATCH_SIZE})")
    else()
        message(STATUS "Unity build enabled for MACE (batch size: unlimited)")
    endif()
endif()

# =============================================================================
# LTO/IPO for MACE
# =============================================================================

if(MACE_ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT MACE_ENABLE_IPO_SUPPORTED
                        OUTPUT MACE_IPO_SUPPORTED_ERROR)
    if(MACE_ENABLE_IPO_SUPPORTED)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
        message(STATUS "LTO/IPO enabled for MACE")
    else()
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE OFF)
        message(NOTICE "***Notice: LTO/IPO not supported. Turning off CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE")
    endif()
endif()

# =============================================================================
# Compile options and definitions for MACE
# =============================================================================

set(MACE_COMPILE_OPTIONS "")
set(MACE_COMPILE_DEFINITIONS "")

# =============================================================================
# Compile warnings for MACE
# =============================================================================

# More warnings
if(CMAKE_COMPILER_IS_GNUCXX)
    list(APPEND MACE_COMPILE_OPTIONS -Wall -Wextra -Wduplicated-cond -Wnon-virtual-dtor -pedantic -Wundef -Wunused-macros)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    list(APPEND MACE_COMPILE_OPTIONS -WCL4 -Wmove -Wnon-virtual-dtor -pedantic -Wundef -Wunused-macros
                                     -Wno-gnu-zero-variadic-macro-arguments)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    list(APPEND MACE_COMPILE_OPTIONS /W4)
endif()

# Surpress some, if needed
if(NOT MACE_SHOW_MORE_COMPILER_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        # # OpenMPI
        # list(APPEND MACE_COMPILE_OPTIONS -Wno-cast-function-type)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 15.0.0)
        #     # backward-cpp
        #     list(APPEND MACE_COMPILE_OPTIONS -Wno-unqualified-std-cast-call)
        # endif()
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS_EQUAL 15.0.0)
            list(APPEND MACE_COMPILE_OPTIONS -Wno-unsupported-friend)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        # ROOT (conditional expression is constant)
        list(APPEND MACE_COMPILE_OPTIONS /wd4127)
        # Common ('argument': conversion from 'type1' to 'type2', possible loss of data)
        list(APPEND MACE_COMPILE_OPTIONS /wd4244)
        # Common ('var': conversion from 'size_t' to 'type', possible loss of data)
        list(APPEND MACE_COMPILE_OPTIONS /wd4267)
        # MSVC std::tuple ('derived class' : destructor was implicitly defined as deleted because a base class destructor is inaccessible or deleted)
        list(APPEND MACE_COMPILE_OPTIONS /wd4624)
        # Common (The file contains a character that cannot be represented in the current code page (number). Save the file in Unicode format to prevent data loss)
        list(APPEND MACE_COMPILE_OPTIONS /wd4819)
        # ROOT (using a function, class member, variable, or typedef that's marked deprecated)
        list(APPEND MACE_COMPILE_OPTIONS /wd4996)
        # Eigen (operator 'operator-name': deprecated between enumerations of different types)
        list(APPEND MACE_COMPILE_OPTIONS /wd5054)
    endif()
# Even more warnings, if needed
elseif(MACE_SHOW_EVEN_MORE_COMPILER_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        list(APPEND MACE_COMPILE_OPTIONS -Weffc++)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        list(APPEND MACE_COMPILE_OPTIONS -Weverything)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        list(APPEND MACE_COMPILE_OPTIONS /Wall)
    endif()
endif()

# =============================================================================
# Other CMake-options-controlled compile options for MACE
# =============================================================================

if(MACE_SIGNAL_HANDLER)
    list(APPEND MACE_COMPILE_DEFINITIONS MACE_SIGNAL_HANDLER=1)
else()
    list(APPEND MACE_COMPILE_DEFINITIONS MACE_SIGNAL_HANDLER=0)
endif()

if(MACE_USE_G4VIS)
    list(APPEND MACE_COMPILE_DEFINITIONS MACE_USE_G4VIS=1)
else()
    list(APPEND MACE_COMPILE_DEFINITIONS MACE_USE_G4VIS=0)
endif()

if(MACE_ENABLE_MSVC_STD_CONFORMITY AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Enable standard-conformity
    list(APPEND MACE_COMPILE_OPTIONS /permissive- /Zc:__cplusplus /Zc:inline)
    message(STATUS "MSVC standard-conformity enabled (/permissive- /Zc:__cplusplus /Zc:inline)")
    # Be permissive to standard cfunctions
    list(APPEND MACE_COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS=1)
endif()

# =============================================================================
# MPI-induced compile options for MACE
# =============================================================================

# Inform OpenMPI not to bring mpicxx in, it's necessary for most cases.
list(APPEND MACE_COMPILE_DEFINITIONS OMPI_SKIP_MPICXX=1)

# Inform MPICH and derivatives not to bring mpicxx in, seems unnecessary but more consistent.
list(APPEND MACE_COMPILE_DEFINITIONS MPICH_SKIP_MPICXX=1)

# =============================================================================
# Eigen-induced compile options for MACE
# =============================================================================

# Inform Eigen not to enable multithreading, though we are not using OpenMP. It is safer to do so.
list(APPEND MACE_COMPILE_DEFINITIONS EIGEN_DONT_PARALLELIZE=1)

if(CMAKE_CXX_PLATFORM_ID STREQUAL "MinGW")
    # MinGW and GCC 12.2 have issues with explitic vectorization
    list(APPEND MACE_COMPILE_DEFINITIONS EIGEN_DONT_VECTORIZE=1)
    message(NOTICE "***Notice: Building on Windows with MinGW, disabling vectorization of Eigen")
endif()

# =============================================================================
# Add definition here
# =============================================================================

add_compile_definitions(${MACE_COMPILE_DEFINITIONS})
