project(Test)

include(${MACE_CMAKE_DIR}/IncludeDirectories.cmake)

add_executable(DescriptionIO DescriptionIO.cxx)
target_link_libraries(DescriptionIO Core)
install(TARGETS DescriptionIO DESTINATION bin)

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry Core ${ROOT_LIBRARIES})
install(TARGETS MakeGeometry DESTINATION bin)

add_executable(TrackConversion TrackConversion.cxx)
target_link_libraries(TrackConversion Core)
install(TARGETS TrackConversion DESTINATION bin)
