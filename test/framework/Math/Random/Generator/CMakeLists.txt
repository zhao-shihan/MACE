project(MACE)

add_executable(MT1993732 MT1993732.cxx)
target_link_libraries(MT1993732 MACEFrameWork)

add_executable(MT1993764 MT1993764.cxx)
target_link_libraries(MT1993764 MACEFrameWork)

add_executable(Xoshiro256Plus Xoshiro256Plus.cxx)
target_link_libraries(Xoshiro256Plus MACEFrameWork)

add_executable(Xoshiro256PP Xoshiro256PP.cxx)
target_link_libraries(Xoshiro256PP MACEFrameWork)

add_executable(Xoshiro256SS Xoshiro256SS.cxx)
target_link_libraries(Xoshiro256SS MACEFrameWork)

add_executable(Xoshiro512Plus Xoshiro512Plus.cxx)
target_link_libraries(Xoshiro512Plus MACEFrameWork)

add_executable(Xoshiro512PP Xoshiro512PP.cxx)
target_link_libraries(Xoshiro512PP MACEFrameWork)

add_executable(Xoshiro512SS Xoshiro512SS.cxx)
target_link_libraries(Xoshiro512SS MACEFrameWork)
