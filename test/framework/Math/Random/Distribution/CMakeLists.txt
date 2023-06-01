project(MACE)

add_executable(Uniform Uniform.c++)
target_link_libraries(Uniform MACEFrameWork)

add_executable(Gaussian Gaussian.c++)
target_link_libraries(Gaussian MACEFrameWork)
