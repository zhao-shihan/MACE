project(Utility)

include_directories(${MPI_CXX_INCLUDE_PATH})
include_directories(${Geant4_INCLUDE_DIRS})
include_directories(${MACE_THIRD_PARTY_DIR}/G4mpi/include)

file(GLOB Utility_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(Utility ${Utility_srcs})
target_link_libraries(Utility ${MPI_CXX_LIBRARIES} ${Geant4_LIBRARIES} G4mpi)
