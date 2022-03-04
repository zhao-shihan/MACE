project(Simulation)

include_directories(${MACE_PROJECT_ROOT_DIR}/Core)
include_directories(${MACE_PROJECT_ROOT_DIR}/Simulation)
include_directories(${MACE_PROJECT_ROOT_DIR}/Utility)

add_subdirectory(SimCalorimeter)
add_subdirectory(SimMACE)
add_subdirectory(SimMTransport)
add_subdirectory(SimSpectrometer)
