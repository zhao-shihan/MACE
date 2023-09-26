# This file is included after "find_package"s and "LookFor"s.

# =============================================================================
# MACE at C++20
# =============================================================================

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
elseif(CMAKE_CXX_STANDARD LESS 20)
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
# LTO/IPO for MACE
# =============================================================================

if(NOT DEFINED CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
endif()
if(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT MACE_ENABLE_IPO_SUPPORTED
                        OUTPUT MACE_IPO_SUPPORTED_ERROR)
    if(MACE_ENABLE_IPO_SUPPORTED)
        message(STATUS "LTO/IPO enabled for MACE")
    else()
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE OFF)
        # message(NOTICE "***Notice: LTO/IPO not supported: \"${MACE_IPO_SUPPORTED_ERROR}\". Turning off CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE")
        message(NOTICE "***Notice: LTO/IPO not supported. Turning off CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE")
    endif()
endif()

# =============================================================================
# Compile warnings for MACE
# =============================================================================

# More warnings
if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -Wduplicated-cond -Wnon-virtual-dtor -pedantic -Wundef -Wunused-macros)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-WCL4 -Wmove -Wnon-virtual-dtor -pedantic -Wundef -Wunused-macros
                        -Wno-gnu-zero-variadic-macro-arguments)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
endif()

# Surpress some, if needed
if(MACE_SURPRESS_USELESS_COMPILE_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        # # OpenMPI
        # add_compile_options(-Wno-cast-function-type)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 15.0.0)
        #     # backward-cpp
        #     add_compile_options(-Wno-unqualified-std-cast-call)
        # endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        # ROOT (conditional expression is constant)
        add_compile_options(/wd4127)
        # Common ('argument': conversion from 'type1' to 'type2', possible loss of data)
        add_compile_options(/wd4244)
        # Common ('var': conversion from 'size_t' to 'type', possible loss of data)
        add_compile_options(/wd4267)
        # MSVC std::tuple ('derived class' : destructor was implicitly defined as deleted because a base class destructor is inaccessible or deleted)
        add_compile_options(/wd4624)
        # Common (The file contains a character that cannot be represented in the current code page (number). Save the file in Unicode format to prevent data loss)
        add_compile_options(/wd4819)
        # ROOT (using a function, class member, variable, or typedef that's marked deprecated)
        add_compile_options(/wd4996)
        # Eigen (operator 'operator-name': deprecated between enumerations of different types)
        add_compile_options(/wd5054)
    endif()
# Even more warnings, if needed
elseif(MACE_SHOW_EVEN_MORE_COMPILE_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        add_compile_options(-Weffc++)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-Weverything)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_options(/Wall)
    endif()
endif()

# =============================================================================
# Other CMake-options-controlled compile options for MACE
# =============================================================================

if(MACE_SIGNAL_HANDLER)
    add_compile_definitions(MACE_SIGNAL_HANDLER=1)
else()
    add_compile_definitions(MACE_SIGNAL_HANDLER=0)
endif()

if(MACE_USE_G4GDML)
    add_compile_definitions(MACE_USE_G4GDML=1)
else()
    add_compile_definitions(MACE_USE_G4GDML=0)
endif()

if(MACE_USE_G4VIS)
    add_compile_definitions(MACE_USE_G4VIS=1)
else()
    add_compile_definitions(MACE_USE_G4VIS=0)
endif()

if(MACE_ENABLE_MSVC_STD_CONFORMITY AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Enable standard-conformity
    add_compile_options(/permissive- /Zc:__cplusplus /Zc:inline)
    message(STATUS "MSVC standard-conformity enabled (/permissive- /Zc:__cplusplus /Zc:inline)")
    # Be permissive to standard cfunctions
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS=1)
endif()

# =============================================================================
# MPI-induced compile options for MACE
# =============================================================================

# Inform OpenMPI not to bring mpicxx in, it's necessary for most cases.
add_compile_definitions(OMPI_SKIP_MPICXX=1)

# Inform MPICH and derivatives not to bring mpicxx in, seems unnecessary but more consistent.
add_compile_definitions(MPICH_SKIP_MPICXX=1)

# =============================================================================
# Eigen-induced compile options for MACE
# =============================================================================

# Inform Eigen not to enable multithreading, though we are not using OpenMP. It is safer to do so.
add_compile_definitions(EIGEN_DONT_PARALLELIZE=1)

if(CMAKE_CXX_PLATFORM_ID STREQUAL "MinGW")
    # MinGW and GCC 12.2 have issues with explitic vectorization
    add_compile_definitions(EIGEN_DONT_VECTORIZE=1)
    message(NOTICE "***Notice: Building on Windows with MinGW, disabling vectorization of Eigen")
endif()
