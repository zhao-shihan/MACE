project(MACE)

add_executable(DescriptionIO DescriptionIO.cxx)
target_link_libraries(DescriptionIO MACEFrameWork MACEDetector)
