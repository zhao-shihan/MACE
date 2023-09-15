project(MACE)

add_executable(RandomNumberDistribution RandomNumberDistribution.c++)
target_link_libraries(RandomNumberDistribution MACEFramework)

add_subdirectory(Distribution)
add_subdirectory(Generator)
