file(GLOB_RECURSE ReconMMSTrack_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

add_executable(ReconMMSTrack ${ReconMMSTrack_srcs})
target_link_libraries(ReconMMSTrack MACEData MACEDetector Mustard::Mustard MACEReconstruction)
target_include_directories(ReconMMSTrack PRIVATE ${GENFIT_INCLUDE_DIRS})

install(TARGETS ReconMMSTrack DESTINATION ${CMAKE_INSTALL_BINDIR})
