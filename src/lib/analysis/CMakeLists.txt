file(GLOB_RECURSE MACE_ANALYSIS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/MACE/*.c++)

add_library(MACEAnalysis STATIC ${MACE_ANALYSIS_SRC})
target_include_directories(MACEAnalysis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(MACEAnalysis PUBLIC MACEData MACEDetector Mustard::Mustard)
