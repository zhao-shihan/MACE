project(MACE)

add_executable(TestSingleton TestSingleton.cxx)
target_link_libraries(TestSingleton MACE)

add_executable(TestFreeSingleton TestFreeSingleton.cxx)
target_link_libraries(TestFreeSingleton MACE)
