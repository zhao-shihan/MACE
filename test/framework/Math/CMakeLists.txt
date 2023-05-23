project(MACE)

add_executable(RALog RALog.cxx)
target_link_libraries(RALog MACEFrameWork)

add_subdirectory(IntegerPower)
add_subdirectory(Random)
