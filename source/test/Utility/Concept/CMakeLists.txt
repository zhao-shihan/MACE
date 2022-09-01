project(MACE)

add_executable(CopyableOrMoveable CopyableOrMoveable.cxx)
target_link_libraries(CopyableOrMoveable MACE)

add_executable(VectorConcept VectorConcept.cxx)
target_link_libraries(VectorConcept MACE)
