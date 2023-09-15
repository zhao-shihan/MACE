project(MACE)

add_executable(Uniform Uniform.c++)
target_link_libraries(Uniform MACEFramework)

add_executable(Gaussian Gaussian.c++)
target_link_libraries(Gaussian MACEFramework)
