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
# MACE compile options
# =============================================================================

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # Enable standard-conformance
    add_compile_options(/permissive- /Zc:__cplusplus /Zc:inline)
    message(STATUS "MSVC standard-conformance mode enabled")
    # Be permissive to standard cfunctions
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# =============================================================================
# Some dependencies specific compile options for MACE
# =============================================================================

# See https://root-forum.cern.ch/t/preprocessor-macro-x86-64-problem-with-clhep-on-windows/50431/2
if(${ROOT_VERSION} VERSION_LESS_EQUAL 6.26.04)
    # We simply define the accidentally involved __uint128_t to a random type and pray that it won't actually be used.
    add_compile_definitions(__uint128_t=float)
endif()

# =============================================================================
# Set compile warnings for MACE
# =============================================================================

# More warnings
if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-Wall -Wextra)
    # GCC -Weffc++
    if(MACE_SHOW_GCC_EFFCXX_COMPILE_WARNINGS AND CMAKE_COMPILER_IS_GNUCXX)
        add_compile_options(-Weffc++)   
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # add_compile_options(/Wall)
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
        # Eigen
        add_compile_options(-Wno-deprecated-enum-enum-conversion)
        # strncpy, strncat, etc.
        add_compile_options(-Wno-stringop-truncation)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # ROOT
        add_compile_options(-Wno-deprecated-volatile)
        # Eigen
        add_compile_options(-Wno-deprecated-anon-enum-enum-conversion)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        
    endif()
endif()
