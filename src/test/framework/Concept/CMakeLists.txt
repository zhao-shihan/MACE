project(MACE)

add_executable(CopyableOrMoveable CopyableOrMoveable.c++)
target_link_libraries(CopyableOrMoveable MACEFramework)

add_executable(VectorConcept VectorConcept.c++)
target_link_libraries(VectorConcept MACEFramework)
