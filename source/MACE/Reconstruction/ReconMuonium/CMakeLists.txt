project(MACE)

file(GLOB_RECURSE ReconMuonium_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_executable(ReconMuonium ${ReconMuonium_srcs})
target_link_libraries(ReconMuonium MACECore MACEUtility)
