project(MACE)

file(GLOB_RECURSE MACE_DETECTOR_SRC ${PROJECT_SOURCE_DIR}/MACE/*.cxx)

add_library(MACEDetector STATIC ${MACE_DETECTOR_SRC})
target_include_directories(MACEDetector PUBLIC ${MACE_PROJECT_SRC_DIR}/detector)
target_link_libraries(MACEDetector MACEFrameWork)
