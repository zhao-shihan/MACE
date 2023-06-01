project(MACE)

file(GLOB_RECURSE ReconMuonium_srcs ${PROJECT_SOURCE_DIR}/*.c++)

add_executable(ReconMuonium ${ReconMuonium_srcs})
target_link_libraries(ReconMuonium MACE)
