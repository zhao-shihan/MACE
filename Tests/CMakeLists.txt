project(Tests)

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry Geometry ${ROOT_LIBRARIES})

add_executable(TrackConversion TrackConversion.cxx)
target_link_libraries(TrackConversion DataModel)

install(TARGETS TrackConversion DESTINATION bin)
install(TARGETS MakeGeometry DESTINATION bin)
