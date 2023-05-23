message(STATUS "Looking for ROOT")

find_package(ROOT 6.28.04 REQUIRED Geom)

message(STATUS "Looking for ROOT - found (version: ${ROOT_VERSION})")
