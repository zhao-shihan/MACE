project(MACE)

file(GLOB_RECURSE MACE_FRAMEWORK_SRC ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MACE STATIC ${MACE_FRAMEWORK_SRC})
target_include_directories(MACE PUBLIC "${MACE_PROJECT_SRC_DIR}/framework" PUBLIC "${ROOT_INCLUDE_DIRS}")
target_link_libraries(MACE argparse::argparse yaml-cpp Eigen3::Eigen MPI::MPI_C ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})
