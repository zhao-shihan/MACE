message(STATUS "Looking for ROOT")

if(MACE_BUILTIN_GENFIT_EVENT_DISPLAY)
    find_package(ROOT 6.28.04 REQUIRED Geom Eve)
else()
    find_package(ROOT 6.28.04 REQUIRED Geom)
endif()

message(STATUS "Looking for ROOT - found (version: ${ROOT_VERSION})")
