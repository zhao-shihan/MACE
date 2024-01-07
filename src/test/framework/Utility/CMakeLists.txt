project(MACE)

add_executable(TestTaskScheduler TestTaskScheduler.c++)
target_link_libraries(TestTaskScheduler MACEFramework)

add_executable(TestDivideIndices TestDivideIndices.c++)
target_link_libraries(TestDivideIndices MACEFramework)
