project(MACE)

add_executable(TestDynamicScheduler TestDynamicScheduler.c++)
target_link_libraries(TestDynamicScheduler MACEFramework)

add_executable(TestStaticScheduler TestStaticScheduler.c++)
target_link_libraries(TestStaticScheduler MACEFramework)
