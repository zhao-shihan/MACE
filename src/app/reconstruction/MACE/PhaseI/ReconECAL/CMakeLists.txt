file(GLOB_RECURSE ReconECAL1_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

add_executable(ReconECAL1 ${ReconECAL1_srcs})
target_link_libraries(ReconECAL1 MACEData MACEDetector Mustard::Mustard)

install(TARGETS ReconECAL1 DESTINATION ${CMAKE_INSTALL_BINDIR})
