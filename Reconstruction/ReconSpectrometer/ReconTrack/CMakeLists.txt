project(ReconTrack)

file(GLOB_RECURSE ReconTrack_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_executable(ReconTrack ${ReconTrack_srcs})
target_link_libraries(ReconTrack DataModel MPITools)

install(TARGETS ReconTrack DESTINATION bin)

