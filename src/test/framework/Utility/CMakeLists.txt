project(MACE)

add_executable(TestStaticScheduler TestStaticScheduler.c++)
target_link_libraries(TestStaticScheduler MACEFramework)

add_executable(TestDivideIndices TestDivideIndices.c++)
target_link_libraries(TestDivideIndices MACEFramework)
