project(Utility)

file(GLOB_RECURSE Utility_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(Utility ${Utility_srcs})
target_link_libraries(Utility ${MPI_CXX_LIBRARIES} ${Geant4_LIBRARIES} G4mpi)
