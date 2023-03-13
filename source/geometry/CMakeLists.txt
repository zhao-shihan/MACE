project(MACE)

file(GLOB_RECURSE MACE_GEOMETRY_SRC ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(MACEGeometry STATIC ${MACE_GEOMETRY_SRC})
target_include_directories(MACEGeometry PUBLIC ${MACE_PROJECT_SRC_DIR}/geometry)
target_link_libraries(MACEGeometry MACEFrameWork)
