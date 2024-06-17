file(GLOB_RECURSE MACE_AnaMACE_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

add_executable(AnaMACE ${MACE_AnaMACE_srcs})
target_link_libraries(AnaMACE MACEData MACEDetector Mustard::Mustard MACEAnalysis)

install(TARGETS AnaMACE DESTINATION bin)
