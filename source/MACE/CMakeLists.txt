project(MACE)

include(${MACE_PROJECT_CMAKE_DIR}/MACECompileWarnings.cmake)
include(${MACE_PROJECT_CMAKE_DIR}/MACEIncludes.cmake)

add_subdirectory(Core)
add_subdirectory(Reconstruction)
add_subdirectory(Simulation)
add_subdirectory(Utility)
