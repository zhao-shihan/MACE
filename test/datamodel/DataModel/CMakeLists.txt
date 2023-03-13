project(MACE)

add_executable(TrackConversion TrackConversion.cxx)
target_link_libraries(TrackConversion MACEDataModel MACEFrameWork)
