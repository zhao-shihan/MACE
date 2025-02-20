file(GLOB_RECURSE MACE_RECONSTRUCTION_SRC ${CMAKE_CURRENT_SOURCE_DIR}/MACE/*.c++)

add_library(MACEReconstruction STATIC ${MACE_RECONSTRUCTION_SRC})
target_include_directories(MACEReconstruction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${GENFIT_INCLUDE_DIRS})
target_link_libraries(MACEReconstruction PUBLIC MACEData MACEDetector Mustard::Mustard genfit2)
