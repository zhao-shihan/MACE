project(Reconstruction)

include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories_recursively(${MACE_PROJECT_ROOT_DIR}/Buildin/GenFit2)
include_directories(${Geant4_INCLUDE_DIRS})

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/*.cc)

add_executable(Reconstruction Reconstruction.cc ${sources})
target_link_libraries(Reconstruction DataModel genfit2 SimG4_static)
