project(MACE)

add_executable(TestDivideIndices TestDivideIndices.cxx)
target_link_libraries(TestDivideIndices MACE)

add_subdirectory(CLHEPVectorX)
add_subdirectory(Concept)
add_subdirectory(Math)
