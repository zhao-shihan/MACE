project(MACE)

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry MACEFrameWork MACEDetector)
