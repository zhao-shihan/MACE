# This file is included before "find_package"s and "LookFor"s.

# =============================================================================
# MACE build type
# =============================================================================

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
    if("${CMAKE_BUILD_TYPE}" STREQUAL "")
        # Default to "Release"
        set(CMAKE_BUILD_TYPE "Release")
    endif()
    message(STATUS "MACE build type: ${CMAKE_BUILD_TYPE}")
endif()

# =============================================================================
# Select MSVC runtime library
# =============================================================================

# Respect to MACE_USE_SHARED_MSVC_RT
if(MACE_USE_SHARED_MSVC_RT)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# =============================================================================
# Global compiler options
# =============================================================================

# Inform OpenMPI not to bring mpicxx in, it's necessary for most cases.
add_compile_definitions(OMPI_SKIP_MPICXX=1)
# Inform MPICH and derivatives not to bring mpicxx in, seems unnecessary but more consistent.
add_compile_definitions(MPICH_SKIP_MPICXX=1)
# Concurrently build with MSVC
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # Build concurrently
    add_compile_options(/MP)
endif()
