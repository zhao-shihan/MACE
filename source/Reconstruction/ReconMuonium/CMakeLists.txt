project(ReconMuonium)

add_executable(ReconMuonium ReconMuonium.cxx)
target_link_libraries(ReconMuonium DataModel Geometry MPITool)
