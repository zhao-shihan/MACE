project(MACE)

include(${MACE_PROJECT_CMAKE_DIR}/CompileWarnings.cmake)
include(${MACE_PROJECT_CMAKE_DIR}/IncludeDirectories.cmake)

add_subdirectory(Core)
add_subdirectory(Reconstruction)
add_subdirectory(Simulation)
add_subdirectory(Utility)
