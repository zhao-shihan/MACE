message(STATUS "Looking for ROOT")

find_package(ROOT 6.24.02 REQUIRED Geom)

message(STATUS "Looking for ROOT - found (version: ${ROOT_VERSION})")
