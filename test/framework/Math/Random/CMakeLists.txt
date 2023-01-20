project(MACE)

add_executable(RandomNumberDistribution RandomNumberDistribution.cxx)
target_link_libraries(RandomNumberDistribution MACE)

add_subdirectory(Distribution)
add_subdirectory(Generator)
