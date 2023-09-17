project(MACE)

add_executable(TestSingleton TestSingleton.c++)
target_link_libraries(TestSingleton MACEFramework)

add_executable(TestPassiveSingleton TestPassiveSingleton.c++)
target_link_libraries(TestPassiveSingleton MACEFramework)
