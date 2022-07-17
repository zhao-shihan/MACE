project(MACE)

# Config for MACE
include(${MACE_PROJECT_CMAKE_DIR}/MACECompileOptions.cmake)

# external
include_directories(${MPI_C_INCLUDE_DIRS})
include_directories(${ROOT_INCLUDE_DIRS})

# Framework
add_subdirectory(framework)
# Simulation
add_subdirectory(simulation)
# Reconstruction
add_subdirectory(reconstruction)
# Test
if(MACE_BUILD_TEST)
    add_subdirectory(test)
endif()
