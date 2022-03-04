project(Reconstruction)

include_directories(${MACE_PROJECT_ROOT_DIR}/Core)
include_directories(${MACE_PROJECT_ROOT_DIR}/Reconstruction)
include_directories(${MACE_PROJECT_ROOT_DIR}/Utility)

add_subdirectory(ReconCalorimeter)
add_subdirectory(ReconSpectrometer)
