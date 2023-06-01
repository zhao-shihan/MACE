project(MACE)

add_executable(DescriptionIO DescriptionIO.c++)
target_link_libraries(DescriptionIO MACEFrameWork MACEDetector)
