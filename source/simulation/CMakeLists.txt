project(MACE)

include_directories("${MACE_PROJECT_SRC_DIR}/simulation")

add_subdirectory(MACE/SimCDC)
add_subdirectory(MACE/SimEMCal)
# add_subdirectory(MACE/SimGuide)
add_subdirectory(MACE/SimMACE)
add_subdirectory(MACE/SimTarget)
