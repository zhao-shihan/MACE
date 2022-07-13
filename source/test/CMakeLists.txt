project(Test)

add_subdirectory(Math)

add_executable(DescriptionIO DescriptionIO.cxx)
target_link_libraries(DescriptionIO MACEUtility MACECore)

add_executable(DivideIndices DivideIndices.cxx)
target_link_libraries(DivideIndices MACEUtility)

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry MACEUtility MACECore ${ROOT_LIBRARIES})

add_executable(TrackConversion TrackConversion.cxx)
target_link_libraries(TrackConversion MACEUtility MACECore)
