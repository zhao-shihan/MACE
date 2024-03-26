project(MACE)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(MACE/ReconMMSTrack)
# add_subdirectory(MACE/ReconEMC)
# add_subdirectory(MACE/ReconMuonium)
# add_subdirectory(MACE/ReconTracks)
add_subdirectory(MACE/SmearMACE)
