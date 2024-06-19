file(GLOB_RECURSE MACE_DATA_MODEL_SRC ${CMAKE_CURRENT_SOURCE_DIR}/MACE/*.c++)

add_library(MACEData STATIC ${MACE_DATA_MODEL_SRC})
target_include_directories(MACEData PUBLIC ${PROJECT_SOURCE_DIR}/lib/data)
target_link_libraries(MACEData PUBLIC Mustard::Mustard)
