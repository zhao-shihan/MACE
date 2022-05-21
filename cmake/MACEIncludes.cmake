# external
include_directories(${MPI_CXX_INCLUDE_DIRS})
include_directories(${Geant4_INCLUDE_DIRS})
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIRS})
# built-in
include_directories(${MACE_BUILDIN_YAML_CPP_DIR}/include)
# intrinsic
include_directories(${MACE_PROJECT_SRC_DIR})
