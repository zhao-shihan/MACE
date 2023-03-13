project(MACE)

add_executable(TestSingleton TestSingleton.cxx)
target_link_libraries(TestSingleton MACEFrameWork)

add_executable(TestFreeSingleton TestFreeSingleton.cxx)
target_link_libraries(TestFreeSingleton MACEFrameWork)
