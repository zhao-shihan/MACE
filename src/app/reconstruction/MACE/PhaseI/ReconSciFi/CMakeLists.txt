file(GLOB_RECURSE ReconSciFi_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

add_executable(ReconSciFi ${ReconSciFi_srcs})
target_link_libraries(ReconSciFi MACEData MACEDetector Mustard::Mustard)

install(TARGETS ReconSciFi DESTINATION ${CMAKE_INSTALL_BINDIR})
