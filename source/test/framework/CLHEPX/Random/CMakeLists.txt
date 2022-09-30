project(MACE)

add_executable(MT32Engine MT32Engine.cxx)
target_link_libraries(MT32Engine MACE)

add_executable(MT64Engine MT64Engine.cxx)
target_link_libraries(MT64Engine MACE)

add_executable(PCG32Engine PCG32Engine.cxx)
target_link_libraries(PCG32Engine MACE)
