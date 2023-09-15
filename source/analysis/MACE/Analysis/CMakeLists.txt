project(MACE)

file(GLOB_RECURSE MACE_ANALYSIS_SRC ${PROJECT_SOURCE_DIR}/*.c++)

add_library(MACEAnalysis STATIC ${MACE_ANALYSIS_SRC})
target_include_directories(MACEAnalysis PUBLIC ${MACE_PROJECT_SRC_DIR}/analysis)
target_link_libraries(MACEAnalysis MACEDataModel MACEDetector MACEFramework)
