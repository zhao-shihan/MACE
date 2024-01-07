project(MACE)

add_executable(TestStaticTaskScheduler TestStaticTaskScheduler.c++)
target_link_libraries(TestStaticTaskScheduler MACEFramework)

add_executable(TestDivideIndices TestDivideIndices.c++)
target_link_libraries(TestDivideIndices MACEFramework)
