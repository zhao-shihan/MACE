# external
include_directories(${MPI_CXX_INCLUDE_DIRS})
include_directories(${Geant4_INCLUDE_DIRS})
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIRS})
# built-in
include_directories(${MACE_EXTERNAL_DIR}/G4mpi/include)
include_directories(${MACE_EXTERNAL_DIR}/yaml-cpp/include)
# intrinsic
include_directories(${MACE_SOURCE_DIR})
