project(MACE)

file(GLOB_RECURSE MACE_DATA_MODEL_SRC ${PROJECT_SOURCE_DIR}/MACE/*.cxx)

add_library(MACEDataModel STATIC ${MACE_DATA_MODEL_SRC})
target_include_directories(MACEDataModel PUBLIC ${MACE_PROJECT_SRC_DIR}/datamodel)
target_link_libraries(MACEDataModel MACEFrameWork)
