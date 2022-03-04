project(MPITools)

include_directories(${MPI_CXX_INCLUDE_PATH})
include_directories(${Geant4_INCLUDE_DIRS})
include_directories(${MACE_THIRD_PARTY_DIR}/G4mpi/include)

file(GLOB MPITools_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MPITools ${MPITools_srcs})
target_link_libraries(MPITools ${MPI_CXX_LIBRARIES} ${Geant4_LIBRARIES} G4mpi)
