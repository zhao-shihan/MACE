# More warnings
if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-Wall -Wextra)
    # GCC -Weffc++
    if(MACE_SHOW_GCC_EFFCXX_COMPILE_WARNINGS AND CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-Weffc++)   
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # add_definitions(/Wall)
    # /Wall will make MSVC commit suicide, just use /W4
    add_definitions(/W4)
endif()
# Surpress those from external
if(MACE_SURPRESS_COMPILE_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        # OpenMPI
        add_definitions(-Wno-cast-function-type)
        # ROOT
        add_definitions(-Wno-volatile)
        if(GCC_VERSION GREATER_EQUAL 11)
            # Eigen
            add_definitions(-Wno-deprecated-enum-enum-conversion)
        endif()
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # ROOT
        add_definitions(-Wno-deprecated-volatile)
        # Eigen
        add_definitions(-Wno-deprecated-anon-enum-enum-conversion)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        
    endif()
endif()
