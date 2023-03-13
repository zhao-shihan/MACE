project(MACE)

add_executable(Uniform Uniform.cxx)
target_link_libraries(Uniform MACEFrameWork)

add_executable(Gaussian Gaussian.cxx)
target_link_libraries(Gaussian MACEFrameWork)
