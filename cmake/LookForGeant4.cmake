message(STATUS "Looking for Geant4")

set(MACE_G4_MINIMUM_REQUIRED 11.0.0)

find_package(Geant4 ${MACE_G4_MINIMUM_REQUIRED} REQUIRED) # to load Geant4Config.cmake

set(MACE_G4_REQUIRED_COMPONENTS "")

if(MACE_ENABLE_VIS)
    list(APPEND MACE_G4_REQUIRED_COMPONENTS vis_all)
endif()

if(MACE_USE_STATIC_G4)
    if(Geant4_static_FOUND)
        list(APPEND MACE_G4_REQUIRED_COMPONENTS static)
    else()
        message(NOTICE "***Notice: MACE_USE_STATIC_G4 is ON but Geant4 reports that static libraries are not found. Dynamic libraries will be linked")
    endif()
endif()

if(NOT MACE_BUILTIN_G4GDML)
    if(Geant4_gdml_FOUND)
        list(APPEND MACE_G4_REQUIRED_COMPONENTS gdml)
    else()
        set(MACE_BUILTIN_G4GDML ON)
        message(NOTICE "***Notice: Geant4::G4gdml not found. Turning on MACE_BUILTIN_G4GDML")
    endif()
endif()

find_package(Geant4 ${MACE_G4_MINIMUM_REQUIRED} REQUIRED ${MACE_G4_REQUIRED_COMPONENTS})
unset(MACE_G4_REQUIRED_COMPONENTS)

if(MACE_BUILTIN_G4GDML)
    # remove possible Geant4::G4gdml from Geant4_LIBRARIES if use built-in G4gdml
    list(REMOVE_ITEM Geant4_LIBRARIES Geant4::G4gdml)
    list(REMOVE_ITEM Geant4_LIBRARIES Geant4::G4gdml-static)
    # configure G4gdml and possibly Xerces-C++
    include(${MACE_PROJECT_CMAKE_DIR}/UseBuiltInG4gdml.cmake)
endif()

message(STATUS "MACE will use Geant4 headers from: ${Geant4_INCLUDE_DIRS}")
message(STATUS "MACE will use Geant4 libraries: ${Geant4_LIBRARIES}")

message(STATUS "Looking for Geant4 - found (version: ${Geant4_VERSION})")
