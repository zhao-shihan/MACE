message(STATUS "Looking for ROOT")

find_package(ROOT 6.24.02 REQUIRED Geom)

message(STATUS "MACE will use ROOT headers from: ${ROOT_INCLUDE_DIRS}")
message(STATUS "MACE will use ROOT libraries: ${ROOT_LIBRARIES}")

message(STATUS "Looking for ROOT - found (version: ${ROOT_VERSION})")
