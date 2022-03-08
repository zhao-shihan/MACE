project(Tests)

add_executable(TrackConversion TrackConversion.cxx)
target_link_libraries(TrackConversion DataModel)

install(TARGETS TrackConversion DESTINATION bin)

