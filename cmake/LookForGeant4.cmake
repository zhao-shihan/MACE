message(STATUS "Looking for Geant4")

set(MACE_G4_MINIMUM_REQUIRED 11.0.0)

find_package(Geant4 ${MACE_G4_MINIMUM_REQUIRED} REQUIRED) # to load Geant4Config.cmake

set(MACE_G4_REQUIRED_COMPONENTS "ui_all")

if(MACE_USE_G4GDML)
    if(Geant4_gdml_FOUND)
        list(APPEND MACE_G4_REQUIRED_COMPONENTS gdml)
    else()
        set(MACE_USE_G4GDML OFF)
        message(NOTICE "***Notice: Geant4::G4gdml not found. Turning off MACE_USE_G4GDML")
    endif()
endif()

if(MACE_USE_G4VIS)
    list(APPEND MACE_G4_REQUIRED_COMPONENTS vis_all)
endif()

if(MACE_USE_STATIC_G4)
    if(Geant4_static_FOUND)
        list(APPEND MACE_G4_REQUIRED_COMPONENTS static)
        message(STATUS "Geant4 static libraries will be linked")
    else()
        message(NOTICE "***Notice: MACE_USE_STATIC_G4 is ON but Geant4 reports that static libraries are not found. Dynamic libraries will be linked")
    endif()
endif()

find_package(Geant4 ${MACE_G4_MINIMUM_REQUIRED} REQUIRED ${MACE_G4_REQUIRED_COMPONENTS})
unset(MACE_G4_REQUIRED_COMPONENTS)

message(STATUS "Looking for Geant4 - found (version: ${Geant4_VERSION})")
