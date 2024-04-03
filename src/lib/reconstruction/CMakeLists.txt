project(MACE)

file(GLOB_RECURSE MACE_RECONSTRUCTION_SRC ${PROJECT_SOURCE_DIR}/MACE/*.c++)

add_library(MACEReconstruction STATIC ${MACE_RECONSTRUCTION_SRC})
target_include_directories(MACEReconstruction PUBLIC ${MACE_PROJECT_SRC_DIR}/lib/reconstruction)
target_link_libraries(MACEReconstruction PUBLIC MACEData MACEDetector MACEFramework genfit2)
