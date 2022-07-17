project(MACE)

add_executable(DescriptionIO DescriptionIO.cxx)
target_link_libraries(DescriptionIO MACE)

add_executable(DivideIndices DivideIndices.cxx)
target_link_libraries(DivideIndices MACE)

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry MACE)

add_executable(TrackConversion TrackConversion.cxx)
target_link_libraries(TrackConversion MACE)

add_subdirectory(Math)
