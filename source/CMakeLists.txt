project(MACE)

# Config for MACE
include(${MACE_PROJECT_CMAKE_DIR}/MACECompileOptions.cmake)

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
