project(Test)

add_subdirectory(Math)

add_executable(CommonMPIWrapper CommonMPIWrapper.cxx)
target_link_libraries(CommonMPIWrapper MACEUtility ${MPI_C_LIBRARIES})

add_executable(DescriptionIO DescriptionIO.cxx)
target_link_libraries(DescriptionIO MACECore)

add_executable(DivideIndices DivideIndices.cxx)
target_link_libraries(DivideIndices MACEUtility)

if(MACE_WITH_G4GDML)
    add_executable(MakeGeometry MakeGeometry.cxx)
    target_link_libraries(MakeGeometry MACECore ${ROOT_LIBRARIES})
endif()

add_executable(TrackConversion TrackConversion.cxx)
target_link_libraries(TrackConversion MACECore)
