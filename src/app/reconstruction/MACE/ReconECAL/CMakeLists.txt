file(GLOB_RECURSE ReconECAL_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

add_executable(ReconECAL ${ReconECAL_srcs})
target_link_libraries(ReconECAL MACEData MACEDetector Mustard::Mustard)

install(TARGETS ReconECAL DESTINATION ${CMAKE_INSTALL_BINDIR})
