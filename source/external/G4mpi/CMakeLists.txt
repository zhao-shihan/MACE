#----------------------------------------------------------------------------------------------------------------
# Informations of MACE edits: 
# 1. All ##MACE_EDIT##. ##MACE_EDIT## at the begin of line means deletion, at end of line means addition
# 2. MACE_EDIT_BEGIN - MACE_EDIT_END blocks
# 3. {message("-- G4 Examples:} -> {message(STATUS "${_projname}:}
#----------------------------------------------------------------------------------------------------------------

# - CmakeLists.txt for G4mpi interface

#------------------------------------------------------------------------------
set(_projname libG4mpi)
set(_targetname G4mpi)
project(${_projname})

#########################
#### MACE_EDIT_BEGIN ####
#########################
if(CMAKE_CXX_STANDARD GREATER 17)
    set(CMAKE_CXX_STANDARD 17)
endif()
message(STATUS "${_projname} will be compiled with C++${CMAKE_CXX_STANDARD}")

if(NOT MACE_SHOW_ALL_COMPILER_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-Wno-cast-function-type)
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        add_definitions(-Wno-implicit-const-int-float-conversion)
    endif()
endif()
#########################
####  MACE_EDIT_END  ####
#########################

#------------------------------------------------------------------------------
#Manadatory dependencies

##MACE_EDIT## cmake_minimum_required(VERSION 3.16...3.21)
##MACE_EDIT## find_package(MPI REQUIRED)
##MACE_EDIT## find_package(Geant4 10.2.0 REQUIRED)
include(${Geant4_USE_FILE})

#------------------------------------------------------------------------------
##MACE_EDIT## message(STATUS "${_projname}: ${_projname} uses includes from: "
##MACE_EDIT##         "${MPI_CXX_INCLUDE_PATH}")
##MACE_EDIT## message(STATUS "${_projname}: ${_projname} uses libraries: ${MPI_CXX_LIBRARIES}")

#Version of this package is the same as the G4 version
set(${_targetname}_VERSION ${Geant4_VERSION})
set(${_targetname}_VERSION_MAJOR ${Geant4_VERSION_MAJOR})
set(${_targetname}_VERSION_MINOR ${Geant4_VERSION_MINOR})
set(${_targetname}_VERSION_PATCH ${Geant4_VERSION_PATCH})

#------------------------------------------------------------------------------
#Options for this package
##MACE_EDIT## option(BUILD_SHARED_LIBS "If true build shared library" ON)
##MACE_EDIT## option(BUILD_STATIC_LIBS "If true build static library" OFF)
set(BUILD_STATIC_LIBS ON) ##MACE_EDIT##
option(G4MPI_OLD_MPI "If true use old signatures for MPI_[Un]Pack functions" 
       OFF)
mark_as_advanced(G4MPI_OLD_MPI)

##MACE_EDIT## # Offer the user the choice of overriding the installation directories
##MACE_EDIT## set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
##MACE_EDIT## set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
##MACE_EDIT## set(INSTALL_INCLUDE_DIR include CACHE PATH
##MACE_EDIT##   "Installation directory for header files")
##MACE_EDIT## #INSTALL_CMAKE_DIR is set later
 
#------------------------------------------------------------------------------
#Setup compilation options specific to this project
add_definitions(-DTOOLS_USE_NATIVE_MPI) 
if(G4MPI_OLD_MPI)
  message(STATUS "${_projname}: ${_projname} using old non-const signatures for" 
          "MPI_[Un]Pack functions")
  add_definitions(-DTOOLS_USE_MPI_PACK_NOT_CONST)
  add_definitions(-DG4MPI_USE_MPI_PACK_NOT_CONST)
  # Prevent warning with c++11 on old MPI 
  add_definitions(-Wno-literal-suffix)
endif()

#------------------------------------------------------------------------------
#TODO: ??? What is G4 policy on this?
#if(Geant4_static_FOUND)
#  set(BUILD_STATIC_LIBS ON)
#  set(BUILD_SHARED_LIBS OFF)
#else()
#  set(BUILD_STATIC_LIBS OFF)
#  set(BUILD_SHARED_LIBS ON)
#endif()

#------------------------------------------------------------------------------
# Define library
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include 
                    ${CMAKE_CURRENT_SOURCE_DIR}/analysis/include 
                    ${Geant4_INCLUDE_DIR} 
                    ${MPI_CXX_INCLUDE_PATH})
link_directories(${MPI_CXX_LIBRARY_DIRS})

set(_sources 
  src/G4MPIbatch.cc
  src/G4MPIextraWorker.cc
  src/G4MPImanager.cc
  src/G4MPImessenger.cc
  src/G4MPIrandomSeedGenerator.cc
  src/G4MPIsession.cc
  src/G4MPIstatus.cc
  src/G4UImpish.cc
  src/G4VMPIseedGenerator.cc
  src/G4VMPIsession.cc
  src/G4MPIscorerMerger.cc
  src/G4MPIhistoMerger.cc
  src/G4MPIntupleMerger.cc
  src/G4VUserMPIrunMerger.cc
  src/G4MPIutils.cc
  analysis/src/G4RootMpiAnalysisManager.cc
  analysis/src/G4RootMpiNtupleFileManager.cc
  analysis/src/G4RootMpiNtupleManager.cc
  analysis/src/G4RootMpiPNtupleManager.cc
)

##MACE_EDIT## #TODO: This works only if both BUILD_STATIC_LIBS=ON && BUILD_SHARED_LIBS=OFF
##MACE_EDIT## #      are explicitly specified, what should be the behavior if only
##MACE_EDIT## #      BUILD_STATIC_LIBS is specified?
##MACE_EDIT## #      In Geant4 both are created: libXXX.so and libXXX.a with two target names
##MACE_EDIT## #      XXX and XXX-static. I should study how to do that...
##MACE_EDIT## if(NOT BUILD_SHARED_LIBS AND NOT BUILD_STATIC_LIBS)
##MACE_EDIT##     message(FATAL "-- G4 Examples: ${_projname} neither static of shared build selected")
##MACE_EDIT##     return()
##MACE_EDIT## endif()
##MACE_EDIT## if(BUILD_STATIC_LIBS)
##MACE_EDIT##   add_library(${_targetname}-static STATIC ${_sources})
##MACE_EDIT##   set_target_properties(${_targetname}-static PROPERTIES OUTPUT_NAME ${_targetname})
##MACE_EDIT##   target_link_libraries(${_targetname}-static ${MPI_CXX_LIBRARIES} ${Geant4_LIBRARIES})
##MACE_EDIT## endif()
##MACE_EDIT## if(BUILD_SHARED_LIBS)
##MACE_EDIT##   add_library(${_targetname} SHARED ${_sources})
##MACE_EDIT##   target_link_libraries(${_targetname} ${MPI_CXX_LIBRARIES} ${Geant4_LIBRARIES})
##MACE_EDIT## endif()
##MACE_EDIT##   add_library(${_targetname}-static STATIC ${_sources})
##MACE_EDIT##   set_target_properties(${_targetname}-static PROPERTIES OUTPUT_NAME ${_targetname})
##MACE_EDIT##   target_link_libraries(${_targetname}-static ${MPI_CXX_LIBRARIES} ${Geant4_LIBRARIES})

#########################
#### MACE_EDIT_BEGIN ####
#########################
add_library(${_targetname} STATIC ${_sources})
set_target_properties(${_targetname} PROPERTIES OUTPUT_NAME ${_targetname})
target_link_libraries(${_targetname} ${MPI_CXX_LIBRARIES} ${Geant4_LIBRARIES})
#########################
####  MACE_EDIT_END  ####
#########################

##MACE_EDIT## # headers
##MACE_EDIT## set(HEADERS
##MACE_EDIT##   include/G4MPIbatch.hh
##MACE_EDIT##   include/G4MPIextraWorker.hh
##MACE_EDIT##   include/G4MPImanager.hh
##MACE_EDIT##   include/G4MPImessenger.hh
##MACE_EDIT##   include/G4MPIrandomSeedGenerator.hh
##MACE_EDIT##   include/G4MPIsession.hh
##MACE_EDIT##   include/G4MPIstatus.hh
##MACE_EDIT##   include/G4UImpish.hh
##MACE_EDIT##   include/G4VMPIextraWorker.hh
##MACE_EDIT##   include/G4VMPIseedGenerator.hh
##MACE_EDIT##   include/G4VMPIsession.hh
##MACE_EDIT##   include/G4MPIscorerMerger.hh
##MACE_EDIT##   include/G4MPIrunMerger.hh
##MACE_EDIT##   include/G4MPIhistoMerger.hh
##MACE_EDIT##   include/G4MPIntupleMerger.hh
##MACE_EDIT##   include/G4VUserMPIrunMerger.hh
##MACE_EDIT##   include/G4MPIutils.hh
##MACE_EDIT##   analysis/include/G4RootMpiAnalysisManager.hh
##MACE_EDIT##   analysis/include/G4RootMpiNtupleFileManager.hh
##MACE_EDIT##   analysis/include/G4RootMpiNtupleManager.hh
##MACE_EDIT##   analysis/include/G4RootMpiPNtupleDescription.hh
##MACE_EDIT##   analysis/include/G4RootMpiPNtupleManager.hh
##MACE_EDIT## 
##MACE_EDIT## )
##MACE_EDIT## 
##MACE_EDIT## #------------------------------------------------------------------------------
##MACE_EDIT## # Overwrite "lib" path w/ "lib64" if needed
##MACE_EDIT## set(_LIBDIR_DEFAULT "lib")
##MACE_EDIT## set(_dolib64 FALSE)
##MACE_EDIT## if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
##MACE_EDIT##   set(_dolib64 TRUE)
##MACE_EDIT## endif()
##MACE_EDIT## #If this is built as part of G4 CMAKE_INSTALL_LIBDIR is defined, we need to
##MACE_EDIT## #so force check of what we should use
##MACE_EDIT## include(Geant4MacroLibraryTargets OPTIONAL RESULT_VARIABLE _internal_build)
##MACE_EDIT## if(_internal_build)
##MACE_EDIT##   set(_dolib64 TRUE)
##MACE_EDIT## endif()
##MACE_EDIT## if(${_dolib64})
##MACE_EDIT##   # Override this default 'lib' with 'lib64' iff:
##MACE_EDIT##   #  - we are on Linux system but NOT cross-compiling
##MACE_EDIT##   #  - we are NOT on debian
##MACE_EDIT##   #  - we are on a 64 bits system
##MACE_EDIT##   # reason is: amd64 ABI: http://www.x86-64.org/documentation/abi.pdf
##MACE_EDIT##   # Note that the future of multi-arch handling may be even
##MACE_EDIT##   # more complicated than that: http://wiki.debian.org/Multiarch
##MACE_EDIT##   if(CMAKE_SYSTEM_NAME MATCHES "Linux"
##MACE_EDIT##       AND NOT CMAKE_CROSSCOMPILING
##MACE_EDIT##       AND NOT EXISTS "/etc/debian_version")
##MACE_EDIT##     if(NOT DEFINED CMAKE_SIZEOF_VOID_P)
##MACE_EDIT##       message(AUTHOR_WARNING
##MACE_EDIT##         "Unable to determine default CMAKE_INSTALL_LIBDIR directory because "
##MACE_EDIT##         "no target architecture is known. "
##MACE_EDIT##         "Please enable at least one language before including GNUInstallDirs.")
##MACE_EDIT##     else()
##MACE_EDIT##       if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
##MACE_EDIT##         set(_LIBDIR_DEFAULT "lib64")
##MACE_EDIT##       endif()
##MACE_EDIT##     endif()
##MACE_EDIT##   endif()
##MACE_EDIT##   set(CMAKE_INSTALL_LIBDIR "${_LIBDIR_DEFAULT}" CACHE PATH "object code libraries (${_LIBDIR_DEFAULT})")
##MACE_EDIT##   set(INSTALL_LIB_DIR ${CMAKE_INSTALL_LIBDIR})
##MACE_EDIT## endif()
##MACE_EDIT## 
##MACE_EDIT## #Set Location of .cmake files
##MACE_EDIT## if(WIN32 AND NOT CYGWIN)
##MACE_EDIT##   set(DEF_INSTALL_CMAKE_DIR CMake)
##MACE_EDIT## else()
##MACE_EDIT##   set(DEF_INSTALL_CMAKE_DIR 
##MACE_EDIT##         ${_LIBDIR_DEFAULT}/${_targetname}-${${_targetname}_VERSION})
##MACE_EDIT## endif()
##MACE_EDIT## set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
##MACE_EDIT##   "Installation directory for CMake files")
##MACE_EDIT## 
##MACE_EDIT## # Make relative paths absolute (needed later on)
##MACE_EDIT## foreach(p LIB BIN INCLUDE CMAKE)
##MACE_EDIT##   set(var INSTALL_${p}_DIR)
##MACE_EDIT##   if(NOT IS_ABSOLUTE "${${var}}")
##MACE_EDIT##     set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
##MACE_EDIT##   endif()
##MACE_EDIT## endforeach()
##MACE_EDIT## 
##MACE_EDIT## #------------------------------------------------------------------------------
##MACE_EDIT## #install
##MACE_EDIT## if(BUILD_SHARED_LIBS)
##MACE_EDIT##   INSTALL(TARGETS ${_targetname}
##MACE_EDIT##           EXPORT ${_targetname}Targets 
##MACE_EDIT##           LIBRARY DESTINATION ${INSTALL_LIB_DIR} COMPONENT shlib)
##MACE_EDIT## endif()
##MACE_EDIT## if(BUILD_STATIC_LIBS)
##MACE_EDIT##    INSTALL(TARGETS ${_targetname}-static
##MACE_EDIT##            EXPORT ${_targetname}Targets 
##MACE_EDIT##            ARCHIVE DESTINATION ${INSTALL_LIB_DIR} COMPONENT dev)
##MACE_EDIT## endif()
##MACE_EDIT## INSTALL(FILES ${HEADERS} DESTINATION include)
##MACE_EDIT## 
##MACE_EDIT## #G4mpiTargets.cmake files
##MACE_EDIT## if(BUILD_SHARED_LIBS)
##MACE_EDIT##     export(TARGETS ${_targetname}
##MACE_EDIT##            FILE "${PROJECT_BINARY_DIR}/${_targetname}Targets.cmake")
##MACE_EDIT## endif()
##MACE_EDIT## if(BUILD_STATIC_LIBS)
##MACE_EDIT##     export(TARGETS ${_targetname}-static
##MACE_EDIT##            FILE "${PROJECT_BINARY_DIR}/${_targetname}Targets.cmake")
##MACE_EDIT## endif()
##MACE_EDIT## # Export the package for use from the build-tree
##MACE_EDIT## # (this registers the build-tree with a global CMake-registry)
##MACE_EDIT## export(PACKAGE ${_projname})
##MACE_EDIT## 
##MACE_EDIT## # Create the G4mpiConfig.cmake and G4mpiConfigVersion files
##MACE_EDIT## set(TARGET_STATIC OFF)
##MACE_EDIT## if(BUILD_STATIC_LIBS AND NOT BUILD_SHARED_LIBS)#If both are activated, prefer shared
##MACE_EDIT##    set(TARGET_STATIC ON)
##MACE_EDIT## endif()
##MACE_EDIT## file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
##MACE_EDIT##        "${INSTALL_INCLUDE_DIR}")
##MACE_EDIT## # ... for the build tree
##MACE_EDIT## set(TARGET_NAME ${_targetname})
##MACE_EDIT## set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
##MACE_EDIT## file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
##MACE_EDIT##    "${INSTALL_INCLUDE_DIR}")
##MACE_EDIT## configure_file(G4mpiConfig.cmake.in
##MACE_EDIT##   "${PROJECT_BINARY_DIR}/${_targetname}Config.cmake" @ONLY)
##MACE_EDIT## # ... for the install tree
##MACE_EDIT## set(CONF_INCLUDE_DIRS "\${${_targetname}_CMAKE_DIR}/${REL_INCLUDE_DIR}")
##MACE_EDIT## configure_file(${_targetname}Config.cmake.in
##MACE_EDIT##   "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${_targetname}Config.cmake" @ONLY)
##MACE_EDIT## # ... for both
##MACE_EDIT## set(THE_VERSION ${${_targetname}_VERSION})
##MACE_EDIT## configure_file(G4mpiConfigVersion.cmake.in
##MACE_EDIT##   "${PROJECT_BINARY_DIR}/${_targetname}ConfigVersion.cmake" @ONLY)
##MACE_EDIT##   
##MACE_EDIT## # Install the G4mpiConfig.cmake 
##MACE_EDIT## install(FILES
##MACE_EDIT##   "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${_targetname}Config.cmake"
##MACE_EDIT##   "${PROJECT_BINARY_DIR}/${_targetname}ConfigVersion.cmake" 
##MACE_EDIT##   DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
##MACE_EDIT## # Install the export set for use with the install-tree
##MACE_EDIT## install(EXPORT ${_targetname}Targets DESTINATION
##MACE_EDIT##   "${INSTALL_CMAKE_DIR}" COMPONENT dev)


