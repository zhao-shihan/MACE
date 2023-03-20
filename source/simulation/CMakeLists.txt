project(MACE)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(MACE/SimCDC)
add_subdirectory(MACE/SimEMCal)
# add_subdirectory(MACE/SimGuide)
add_subdirectory(MACE/SimMACE)
add_subdirectory(MACE/SimTarget)
