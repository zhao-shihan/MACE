project(MACE)

file(GLOB_RECURSE MACE_ANALYSIS_SRC ${PROJECT_SOURCE_DIR}/MACE/*.c++)

add_library(MACEAnalysis STATIC ${MACE_ANALYSIS_SRC})
target_include_directories(MACEAnalysis PUBLIC ${MACE_PROJECT_SRC_DIR}/lib/analysis)
target_link_libraries(MACEAnalysis PUBLIC MACEDataModel MACEDetector MACEFramework)
