project(MACE)

include_directories("${MACE_PROJECT_SRC_DIR}/reconstruction")

add_subdirectory(MACE/ReconEMCal)
add_subdirectory(MACE/ReconMuonium)
add_subdirectory(MACE/ReconTracks)
