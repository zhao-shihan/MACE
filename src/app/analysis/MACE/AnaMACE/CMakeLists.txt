project(MACE)

file(GLOB_RECURSE MACE_AnaMACE_srcs ${PROJECT_SOURCE_DIR}/*.c++)

add_executable(AnaMACE ${MACE_AnaMACE_srcs})
target_link_libraries(AnaMACE MACEDataModel MACEDetector MACEFramework MACEAnalysis)

install(TARGETS AnaMACE DESTINATION bin)
