project(MACE)

add_executable(RALog RALog.c++)
target_link_libraries(RALog MACEFramework)

add_subdirectory(IntegerPower)
add_subdirectory(Random)
