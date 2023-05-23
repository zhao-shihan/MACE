project(MACE)

file(GLOB_RECURSE ReconCDCTrack_srcs ${PROJECT_SOURCE_DIR}/*.cxx)

add_executable(ReconCDCTrack ${ReconCDCTrack_srcs})
target_link_libraries(ReconCDCTrack MACEDataModel MACEDetector MACEFrameWork genfit2)
target_include_directories(ReconCDCTrack PRIVATE ${GENFIT_INCLUDE_DIRS})

install(TARGETS ReconCDCTrack DESTINATION bin)
