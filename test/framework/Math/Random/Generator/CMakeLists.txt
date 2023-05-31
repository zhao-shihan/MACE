project(MACE)

add_executable(MT1993732 MT1993732.cxx)
target_link_libraries(MT1993732 MACEFrameWork)

add_executable(MT1993764 MT1993764.cxx)
target_link_libraries(MT1993764 MACEFrameWork)

add_executable(Xoshiro256Plus Xoshiro256Plus.cxx)
target_link_libraries(Xoshiro256Plus MACEFrameWork)

add_executable(Xoshiro256PP Xoshiro256PP.cxx)
target_link_libraries(Xoshiro256PP MACEFrameWork)

add_executable(Xoshiro256MM Xoshiro256MM.cxx)
target_link_libraries(Xoshiro256MM MACEFrameWork)

add_executable(Xoshiro512Plus Xoshiro512Plus.cxx)
target_link_libraries(Xoshiro512Plus MACEFrameWork)

add_executable(Xoshiro512PP Xoshiro512PP.cxx)
target_link_libraries(Xoshiro512PP MACEFrameWork)

add_executable(Xoshiro512MM Xoshiro512MM.cxx)
target_link_libraries(Xoshiro512MM MACEFrameWork)
