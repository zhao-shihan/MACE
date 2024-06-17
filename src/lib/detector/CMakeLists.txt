file(GLOB_RECURSE MACE_DETECTOR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/MACE/*.c++)

add_library(MACEDetector STATIC ${MACE_DETECTOR_SRC})
target_include_directories(MACEDetector PUBLIC ${PROJECT_SOURCE_DIR}/lib/detector)
target_link_libraries(MACEDetector PUBLIC Mustard::Mustard
                                   PRIVATE pmp)
target_compile_definitions(MACEDetector PRIVATE PMP_SCALAR_TYPE_64=1
                                                PMP_INDEX_TYPE_64=1)
