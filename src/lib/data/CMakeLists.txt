project(MACE)

file(GLOB_RECURSE MACE_DATA_MODEL_SRC ${PROJECT_SOURCE_DIR}/MACE/*.c++)

add_library(MACEData STATIC ${MACE_DATA_MODEL_SRC})
target_include_directories(MACEData PUBLIC ${MACE_PROJECT_SRC_DIR}/lib/data)
target_link_libraries(MACEData PUBLIC MACEFramework)
