file(GLOB_RECURSE ReconMRPC_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

add_executable(ReconMRPC ${ReconMRPC_srcs})
target_link_libraries(ReconMRPC MACEData MACEDetector Mustard::Mustard)

install(TARGETS ReconMRPC DESTINATION ${CMAKE_INSTALL_BINDIR})
