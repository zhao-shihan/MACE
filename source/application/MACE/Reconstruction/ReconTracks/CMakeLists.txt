project(MACE)

file(GLOB_RECURSE ReconTracks_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_executable(ReconTracks ${ReconTracks_srcs})
target_link_libraries(ReconTracks MACE)

install(TARGETS ReconTracks DESTINATION bin)

