file(GLOB_RECURSE ReconMuonium_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

add_executable(ReconMuonium ${ReconMuonium_srcs})
target_link_libraries(ReconMuonium MACE)
