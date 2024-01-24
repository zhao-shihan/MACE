project(MACE)

add_executable(TestMuonIPPDecay TestMuonIPPDecay.c++)
target_link_libraries(TestMuonIPPDecay MACESimulation)
