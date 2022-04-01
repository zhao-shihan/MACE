project(Test)

include(${MACE_CMAKE_DIR}/IncludeDirectories.cmake)

add_executable(DescriptionIO DescriptionIO.cxx)
target_link_libraries(DescriptionIO Geometry)
install(TARGETS DescriptionIO DESTINATION bin)

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry Geometry ${ROOT_LIBRARIES})
install(TARGETS MakeGeometry DESTINATION bin)

add_executable(TrackConversion TrackConversion.cxx)
target_link_libraries(TrackConversion DataModel)
install(TARGETS TrackConversion DESTINATION bin)
