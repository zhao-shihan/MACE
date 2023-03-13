project(MACE)

add_executable(DescriptionIO DescriptionIO.cxx)
target_link_libraries(DescriptionIO MACEFrameWork MACEGeometry)

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry MACEFrameWork MACEGeometry)
