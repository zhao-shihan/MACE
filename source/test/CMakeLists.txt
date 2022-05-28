project(Test)

include(${MACE_PROJECT_CMAKE_DIR}/MACECompileWarnings.cmake)
include(${MACE_PROJECT_CMAKE_DIR}/MACEIncludes.cmake)

add_executable(CommonMPIWrapper CommonMPIWrapper.cxx)
target_link_libraries(CommonMPIWrapper MACEUtility ${MPI_C_LIBRARIES})
#install(TARGETS CommonMPIWrapper DESTINATION bin)

add_executable(DescriptionIO DescriptionIO.cxx)
target_link_libraries(DescriptionIO MACECore)
#install(TARGETS DescriptionIO DESTINATION bin)

add_executable(DivideIndices DivideIndices.cxx)
target_link_libraries(DivideIndices MACEUtility)
#install(TARGETS DivideIndices DESTINATION bin)

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry MACECore ${ROOT_LIBRARIES})
#install(TARGETS MakeGeometry DESTINATION bin)

add_executable(TestPowInt TestPowInt.cxx)
target_link_libraries(TestPowInt)
#install(TARGETS CommonMPIWrapper DESTINATION bin)

add_executable(TrackConversion TrackConversion.cxx)
target_link_libraries(TrackConversion MACECore)
#install(TARGETS TrackConversion DESTINATION bin)
