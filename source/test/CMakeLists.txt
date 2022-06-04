project(Test)

include(${MACE_PROJECT_CMAKE_DIR}/MACECompileWarnings.cmake)
include(${MACE_PROJECT_CMAKE_DIR}/MACEIncludes.cmake)

add_subdirectory(Math)

add_executable(CommonMPIWrapper CommonMPIWrapper.cxx)
target_link_libraries(CommonMPIWrapper MACEUtility ${MPI_LIBRARIES})

add_executable(DescriptionIO DescriptionIO.cxx)
target_link_libraries(DescriptionIO MACECore)

add_executable(DivideIndices DivideIndices.cxx)
target_link_libraries(DivideIndices MACEUtility)

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry MACECore ${ROOT_LIBRARIES})

add_executable(TrackConversion TrackConversion.cxx)
target_link_libraries(TrackConversion MACECore)
