file(GLOB_RECURSE ReconPhaseI_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

add_executable(ReconPhaseI ${ReconPhaseI_srcs})
target_link_libraries(ReconPhaseI MACEData MACEDetector Mustard::Mustard)

install(TARGETS ReconPhaseI DESTINATION ${CMAKE_INSTALL_BINDIR})
