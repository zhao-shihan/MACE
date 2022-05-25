# More warnings
add_definitions(-Wall -Wextra)
# Surpress those from external
if(NOT MACE_SHOW_ALL_COMPILE_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        # Open MPI
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
