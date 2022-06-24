project(G4gdml)

# following G4 config faithfully
include(${Geant4_USE_FILE})

message(STATUS "G4gdml will use Xerces-C++ headers from: ${XercesC_INCLUDE_DIR}")
message(STATUS "G4gdml will use Xerces-C++ libraries: ${XercesC_LIBRARIES}")
message(STATUS "G4gdml will use Geant4 headers from: ${Geant4_INCLUDE_DIRS}")
message(STATUS "G4gdml will use Geant4 libraries: ${Geant4_LIBRARIES}")

# G4gdml sources
file(GLOB G4gdml_srcs "${PROJECT_SOURCE_DIR}/src/*.cc")

# target
add_library(G4gdml STATIC ${G4gdml_srcs})
target_include_directories(G4gdml PRIVATE ${XercesC_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(G4gdml ${Geant4_LIBRARIES} ${XercesC_LIBRARIES})
