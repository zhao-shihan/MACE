project(MACE)

file(GLOB_RECURSE ReconCDCTrack_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_executable(ReconCDCTrack ${ReconCDCTrack_srcs})
target_include_directories(ReconCDCTrack PUBLIC ${MACE_PROJECT_SRC_DIR}/detector)
target_link_libraries(ReconCDCTrack MACEDataModel MACEFrameWork)

install(TARGETS ReconCDCTrack DESTINATION bin)
