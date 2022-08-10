project(MACE)

add_executable(CLHEPVectorData CLHEPVectorData.cxx)
target_link_libraries(CLHEPVectorData MACE)

add_executable(CopyableOrMoveable CopyableOrMoveable.cxx)
target_link_libraries(CopyableOrMoveable MACE)

add_executable(DescriptionIO DescriptionIO.cxx)
target_link_libraries(DescriptionIO MACE)

add_executable(DivideIndices DivideIndices.cxx)
target_link_libraries(DivideIndices MACE)

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry MACE)

add_executable(TrackConversion TrackConversion.cxx)
target_link_libraries(TrackConversion MACE)

add_executable(VectorConcept VectorConcept.cxx)
target_link_libraries(VectorConcept MACE)
