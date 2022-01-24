project(Reconstruction)

include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})
# include_directories_recursively(${MACE_THIRD_PARTY_DIR}/GenFit2)
include_directories(${Geant4_INCLUDE_DIRS})

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/*.cxx)

add_executable(Reconstruction Reconstruction.cxx ${sources})
# target_link_libraries(Reconstruction DataModel genfit2 SimG4_static)
target_link_libraries(Reconstruction DataModel SimG4_static)

install(TARGETS Reconstruction DESTINATION bin)