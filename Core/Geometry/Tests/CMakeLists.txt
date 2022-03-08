project(Tests)

add_executable(MakeGeometry MakeGeometry.cxx)
target_link_libraries(MakeGeometry Geometry ${ROOT_LIBRARIES})

install(TARGETS MakeGeometry DESTINATION bin)

