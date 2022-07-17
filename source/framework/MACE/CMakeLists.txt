project(MACE)

file(GLOB_RECURSE MACE_FRAMEWORK_SRC ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MACE STATIC ${MACE_FRAMEWORK_SRC})
target_link_libraries(MACE yaml-cpp Eigen3::Eigen ${MPI_C_LIBRARIES} ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})
