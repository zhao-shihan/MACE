project(MACE)

add_executable(MakeGeometry MakeGeometry.c++)
target_link_libraries(MakeGeometry MACEFrameWork MACEDetector)
