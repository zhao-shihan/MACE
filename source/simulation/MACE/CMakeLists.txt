project(MACE)

include_directories("${MACE_PROJECT_SRC_DIR}/framework")

add_subdirectory(SimCDC)
add_subdirectory(SimEMCal)
add_subdirectory(SimMACE)
add_subdirectory(SimTarget)
