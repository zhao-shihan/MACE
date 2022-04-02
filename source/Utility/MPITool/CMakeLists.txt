project(MPITool)

file(GLOB MPITool_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MPITool ${MPITool_srcs})
target_link_libraries(MPITool ${MPI_CXX_LIBRARIES} ${Geant4_LIBRARIES} G4mpi)
