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
# CMake controllable compile options for MACE
# =============================================================================

if(MACE_SIGNAL_HANDLER)
    add_compile_definitions(MACE_SIGNAL_HANDLER=1)
endif()

if(MACE_WITH_G4GDML)
    add_compile_definitions(MACE_WITH_G4GDML=1)
endif()

if(MACE_WITH_G4VIS)
    add_compile_definitions(MACE_WITH_G4VIS=1)
endif()

if(MACE_ENABLE_LTO)
    if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options(-flto)
        add_link_options(-flto)
        message(STATUS "LTO enabled for MACE (-flto)")
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        add_link_options(/LTCG)
        message(STATUS "LTO enabled for MACE (/LTCG)")
    endif()
endif()

if(MACE_ENABLE_MSVC_STD_CONFORMITY)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        # Enable standard-conformity
        add_compile_options(/permissive- /Zc:__cplusplus /Zc:inline)
        message(STATUS "MSVC standard-conformity enabled (/permissive- /Zc:__cplusplus /Zc:inline)")
        # Be permissive to standard cfunctions
        add_compile_definitions(_CRT_SECURE_NO_WARNINGS=1)
    endif()
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

if("${CMAKE_CXX_PLATFORM_ID}" STREQUAL "MinGW")
    # MinGW and GCC 12.2 have issues with explitic vectorization
    add_compile_definitions(EIGEN_DONT_VECTORIZE=1)
    message(NOTICE "***Notice: Building on Windows with MinGW, disabling vectorization of Eigen")
endif()

# =============================================================================
# ROOT-induced compile options for MACE
# =============================================================================

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    # See https://root-forum.cern.ch/t/preprocessor-macro-x86-64-problem-with-clhep-on-windows/50431
    if(${ROOT_VERSION} VERSION_LESS_EQUAL 6.26.04)
        # We simply define the accidentally involved __uint128_t to a random type and pray that it won't actually be used.
        add_compile_definitions(__uint128_t=char******)
        message(NOTICE "***Notice: Building on Windows with ROOT ${ROOT_VERSION}, defining __uint128_t to another random type.")
        message(NOTICE "           See https://root-forum.cern.ch/t/preprocessor-macro-x86-64-problem-with-clhep-on-windows/50431")
    endif()
endif()

# Solve conflict between <span> and "ROOT/RSpan.hxx"
add_compile_definitions(R__HAS_STD_SPAN=1)

# =============================================================================
# Compile warnings for MACE
# =============================================================================

# More warnings
if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-Wall -Wextra)
    # GCC -Weffc++
    if(MACE_SHOW_GCC_EFFCXX_COMPILE_WARNINGS AND CMAKE_COMPILER_IS_GNUCXX)
        add_compile_options(-Weffc++)   
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # /Wall will make MSVC commit suicide, just use /W4
    add_compile_options(/W4)
endif()
# Surpress those stupid or from external
if(MACE_SURPRESS_COMPILE_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        # OpenMPI
        add_compile_options(-Wno-cast-function-type)
        # ROOT
        add_compile_options(-Wno-volatile)
        # strncpy, strncat, etc.
        add_compile_options(-Wno-stringop-truncation)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # ROOT
        add_compile_options(-Wno-deprecated-volatile)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
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
endif()
