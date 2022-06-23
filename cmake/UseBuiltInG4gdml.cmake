message(STATUS "MACE will use built-in G4gdml")

# look for Xerces-C++
include(${MACE_PROJECT_CMAKE_DIR}/LookForXercesC.cmake)
# append Xerces-C++ to Geant4_INCLUDE_DIRS and Geant4_LIBRARIES
list(APPEND Geant4_INCLUDE_DIRS "${XercesC_INCLUDE_DIR}")
list(APPEND Geant4_LIBRARIES "${XercesC_LIBRARIES}")

set(MACE_BUILTIN_G4GDML_DIR "${MACE_PROJECT_3RDPARTY_DIR}/G4gdml")
# configuring G4gdml
message(STATUS "---------------------------------------------------------------------------")
message(STATUS "Configuring built-in G4gdml")
message(STATUS "---------------------------------------------------------------------------")
add_subdirectory("${MACE_BUILTIN_G4GDML_DIR}")
message(STATUS "---------------------------------------------------------------------------")
message(STATUS "Configuring built-in G4gdml - done")
message(STATUS "---------------------------------------------------------------------------")
# append G4gdml to Geant4_INCLUDE_DIRS and Geant4_LIBRARIES
list(APPEND Geant4_INCLUDE_DIRS "${MACE_BUILTIN_G4GDML_DIR}/include")
list(APPEND Geant4_LIBRARIES G4gdml)
