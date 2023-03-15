project(MACE)

add_executable(MT32Engine MT32Engine.cxx)
target_link_libraries(MT32Engine MACEFrameWork)

add_executable(MT64Engine MT64Engine.cxx)
target_link_libraries(MT64Engine MACEFrameWork)

add_executable(Xoshiro256Engine Xoshiro256Engine.cxx)
target_link_libraries(Xoshiro256Engine MACEFrameWork)
