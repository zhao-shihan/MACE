project(MPITools)

file(GLOB MPITools_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MPITools ${MPITools_srcs})
target_link_libraries(MPITools ${MPI_CXX_LIBRARIES} ${Geant4_LIBRARIES} G4mpi)

