project(Test)

add_subdirectory(Math)

add_executable(DescriptionIO DescriptionIO.cxx)
target_link_libraries(DescriptionIO MACEUtility MACEEnvironment MACECore)

add_executable(DivideIndices DivideIndices.cxx)
target_link_libraries(DivideIndices MACEUtility MACEEnvironment)

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry MACEUtility MACEEnvironment MACECore ${ROOT_LIBRARIES})

add_executable(TrackConversion TrackConversion.cxx)
target_link_libraries(TrackConversion MACEUtility MACEEnvironment MACECore)
