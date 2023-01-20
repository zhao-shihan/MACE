project(MACE)

add_executable(Uniform Uniform.cxx)
target_link_libraries(Uniform MACE)

add_executable(Gaussian Gaussian.cxx)
target_link_libraries(Gaussian MACE)
