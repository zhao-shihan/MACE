# More warnings
add_definitions(-Wall -Wextra)
if(MACE_SHOW_EFFCXX_COMPILE_WARNINGS)
    add_definitions(-Weffc++)
endif()
# Surpress those from external
if(MACE_SURPRESS_COMPILE_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        # OpenMPI
        add_definitions(-Wno-cast-function-type)
        # ROOT
        add_definitions(-Wno-volatile)
        if(GCC_VERSION GREATER_EQUAL 11)
            # Eigen3
            add_definitions(-Wno-deprecated-enum-enum-conversion)
        endif()
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        # ROOT
        add_definitions(-Wno-deprecated-volatile)
        # Eigen3
        add_definitions(-Wno-deprecated-anon-enum-enum-conversion)
    endif()
endif()
