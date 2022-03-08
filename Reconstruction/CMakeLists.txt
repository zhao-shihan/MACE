project(Reconstruction)

include_directories(${MACE_PROJECT_ROOT_DIR}/Reconstruction)

add_subdirectory(ReconCalorimeter)
add_subdirectory(ReconMuonium)
add_subdirectory(ReconSpectrometer)

