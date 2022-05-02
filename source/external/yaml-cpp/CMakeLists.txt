#----------------------------------------------------------------------------------------------------------------
# Informations of MACE edits: 
# 1. All ##MACE_EDIT##. ##MACE_EDIT## at the begin of line means deletion, at end of line means addition
# 2. MACE_EDIT_BEGIN - MACE_EDIT_END blocks
#----------------------------------------------------------------------------------------------------------------

message(STATUS "YAML_CPP will be compiled with C++${CMAKE_CXX_STANDARD}") ##MACE_EDIT##

##MACE_EDIT## # 3.5 is actually available almost everywhere, but this a good minimum
##MACE_EDIT## cmake_minimum_required(VERSION 3.4)

##MACE_EDIT## # enable MSVC_RUNTIME_LIBRARY target property
##MACE_EDIT## # see https://cmake.org/cmake/help/latest/policy/CMP0091.html
##MACE_EDIT## if(POLICY CMP0091)
##MACE_EDIT##   cmake_policy(SET CMP0091 NEW)
##MACE_EDIT## endif()

project(YAML_CPP VERSION 0.7.0 LANGUAGES CXX)

##MACE_EDIT## include(CMakePackageConfigHelpers)
##MACE_EDIT## include(CMakeDependentOption)
##MACE_EDIT## include(CheckCXXCompilerFlag)
##MACE_EDIT## include(GNUInstallDirs)
##MACE_EDIT## include(CTest)

##MACE_EDIT## find_program(YAML_CPP_CLANG_FORMAT_EXE NAMES clang-format)

##MACE_EDIT## option(YAML_CPP_BUILD_CONTRIB "Enable yaml-cpp contrib in library" ON)
set(YAML_CPP_BUILD_CONTRIB ON) ##MACE_EDIT##
##MACE_EDIT## option(YAML_CPP_BUILD_TOOLS "Enable parse tools" ON)
##MACE_EDIT## option(YAML_BUILD_SHARED_LIBS "Build yaml-cpp shared library" ${BUILD_SHARED_LIBS})

##MACE_EDIT## cmake_dependent_option(YAML_CPP_BUILD_TESTS
##MACE_EDIT##   "Enable yaml-cpp tests" ON
##MACE_EDIT##   "BUILD_TESTING;CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)
##MACE_EDIT## cmake_dependent_option(YAML_CPP_INSTALL
##MACE_EDIT##   "Enable generation of yaml-cpp install targets" ON
##MACE_EDIT##   "CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)
##MACE_EDIT## cmake_dependent_option(YAML_MSVC_SHARED_RT
##MACE_EDIT##   "MSVC: Build yaml-cpp with shared runtime libs (/MD)" ON
##MACE_EDIT##   "MSVC" OFF)

set(yaml-cpp-type STATIC)
set(yaml-cpp-label-postfix "static")
if (YAML_BUILD_SHARED_LIBS)
  set(yaml-cpp-type SHARED)
  set(yaml-cpp-label-postfix "shared")
endif()

set(build-shared $<BOOL:${YAML_BUILD_SHARED_LIBS}>)
set(build-windows-dll $<AND:$<BOOL:${CMAKE_HOST_WIN32}>,${build-shared}>)
set(not-msvc $<NOT:$<CXX_COMPILER_ID:MSVC>>)
set(msvc-shared_rt $<BOOL:${YAML_MSVC_SHARED_RT}>)

if (NOT DEFINED CMAKE_MSVC_RUNTIME_LIBRARY)
  set(CMAKE_MSVC_RUNTIME_LIBRARY
    MultiThreaded$<$<CONFIG:Debug>:Debug>$<${msvc-shared_rt}:DLL>)
endif()

set(contrib-pattern "src/contrib/*.cpp")
set(src-pattern "src/*.cpp")
if (CMAKE_VERSION VERSION_GREATER 3.12)
  list(INSERT contrib-pattern 0 CONFIGURE_DEPENDS)
  list(INSERT src-pattern 0 CONFIGURE_DEPENDS)
endif()

file(GLOB yaml-cpp-contrib-sources ${contrib-pattern})
file(GLOB yaml-cpp-sources ${src-pattern})

set(msvc-rt $<TARGET_PROPERTY:MSVC_RUNTIME_LIBRARY>)

set(msvc-rt-mtd-static $<STREQUAL:${msvc-rt},MultiThreadedDebug>)
set(msvc-rt-mt-static $<STREQUAL:${msvc-rt},MultiThreaded>)

set(msvc-rt-mtd-dll $<STREQUAL:${msvc-rt},MultiThreadedDebugDLL>)
set(msvc-rt-mt-dll $<STREQUAL:${msvc-rt},MultiThreadedDLL>)

set(backport-msvc-runtime $<VERSION_LESS:${CMAKE_VERSION},3.15>)

add_library(yaml-cpp ${yaml-cpp-type} "")
add_library(yaml-cpp::yaml-cpp ALIAS yaml-cpp)

set_property(TARGET yaml-cpp
  PROPERTY
    MSVC_RUNTIME_LIBRARY ${CMAKE_MSVC_RUNTIME_LIBRARY})
set_property(TARGET yaml-cpp
  PROPERTY
    CXX_STANDARD_REQUIRED ON)

target_include_directories(yaml-cpp
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set_target_properties(yaml-cpp
    PROPERTIES
      CXX_STANDARD 11)
endif()

target_compile_options(yaml-cpp
  PRIVATE
    #########################
    #### MACE_EDIT_BEGIN ####
    #########################
    #
    # Suppress warning:
    #
    # ../ThirdParty/yaml-cpp/include/yaml-cpp/node/impl.h: In member function ‘YAML::Node& YAML::Node::operator=(const T&)’:
    # ../ThirdParty/yaml-cpp/include/yaml-cpp/node/impl.h:206:10: warning: ‘operator=’ should return a reference to ‘*this’ [-Weffc++]
    #   206 |   return *this;
    #       |          ^~~~~
    #
    #########################
    ####  MACE_EDIT_END  ####
    #########################
    ##MACE_EDIT## $<${not-msvc}:-Wall -Wextra -Wshadow -Weffc++ -Wno-long-long>
    $<${not-msvc}:-Wall -Wextra -Wshadow -Wno-long-long> ##MACE_EDIT##
    $<${not-msvc}:-pedantic -pedantic-errors>

    $<$<AND:${backport-msvc-runtime},${msvc-rt-mtd-static}>:-MTd>
    $<$<AND:${backport-msvc-runtime},${msvc-rt-mt-static}>:-MT>
    $<$<AND:${backport-msvc-runtime},${msvc-rt-mtd-dll}>:-MDd>
    $<$<AND:${backport-msvc-runtime},${msvc-rt-mt-dll}>:-MD>

    # /wd4127 = disable warning C4127 "conditional expression is constant"
    # http://msdn.microsoft.com/en-us/library/6t66728h.aspx
    # /wd4355 = disable warning C4355 "'this' : used in base member initializer list
    # http://msdn.microsoft.com/en-us/library/3c594ae3.aspx
    $<$<CXX_COMPILER_ID:MSVC>:/W3 /wd4127 /wd4355>)

target_compile_definitions(yaml-cpp
  PRIVATE
    $<${build-windows-dll}:${PROJECT_NAME}_DLL>
    $<$<NOT:$<BOOL:${YAML_CPP_BUILD_CONTRIB}>>:YAML_CPP_NO_CONTRIB>)

target_sources(yaml-cpp
  PRIVATE
    $<$<BOOL:${YAML_CPP_BUILD_CONTRIB}>:${yaml-cpp-contrib-sources}>
    ${yaml-cpp-sources})

if (NOT DEFINED CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX "d")
endif()

set_target_properties(yaml-cpp PROPERTIES
  VERSION "${PROJECT_VERSION}"
  SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  PROJECT_LABEL "yaml-cpp ${yaml-cpp-label-postfix}"
  DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")

##MACE_EDIT## configure_package_config_file(
##MACE_EDIT##   "${PROJECT_SOURCE_DIR}/yaml-cpp-config.cmake.in"
##MACE_EDIT##   "${PROJECT_BINARY_DIR}/yaml-cpp-config.cmake"
##MACE_EDIT##   INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/yaml-cpp")
##MACE_EDIT## 
##MACE_EDIT## write_basic_package_version_file(
##MACE_EDIT##   "${PROJECT_BINARY_DIR}/yaml-cpp-config-version.cmake"
##MACE_EDIT##   COMPATIBILITY AnyNewerVersion)
##MACE_EDIT## 
##MACE_EDIT## configure_file(yaml-cpp.pc.in yaml-cpp.pc @ONLY)
##MACE_EDIT## 
##MACE_EDIT## if (YAML_CPP_INSTALL)
##MACE_EDIT## 	install(TARGETS yaml-cpp
##MACE_EDIT##     EXPORT yaml-cpp-targets
##MACE_EDIT##     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
##MACE_EDIT##     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
##MACE_EDIT##     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
##MACE_EDIT## 	install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
##MACE_EDIT##     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
##MACE_EDIT## 		FILES_MATCHING PATTERN "*.h")
##MACE_EDIT##   install(EXPORT yaml-cpp-targets
##MACE_EDIT##     DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/yaml-cpp")
##MACE_EDIT## 	install(FILES
##MACE_EDIT## 		"${PROJECT_BINARY_DIR}/yaml-cpp-config.cmake"
##MACE_EDIT## 		"${PROJECT_BINARY_DIR}/yaml-cpp-config-version.cmake"
##MACE_EDIT##     DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/yaml-cpp")
##MACE_EDIT##   install(FILES "${PROJECT_BINARY_DIR}/yaml-cpp.pc"
##MACE_EDIT##     DESTINATION ${CMAKE_INSTALL_DATADIR}/pkgconfig)
##MACE_EDIT## endif()
##MACE_EDIT## 
##MACE_EDIT## if(YAML_CPP_BUILD_TESTS)
##MACE_EDIT## 	add_subdirectory(test)
##MACE_EDIT## endif()
##MACE_EDIT## 
##MACE_EDIT## if(YAML_CPP_BUILD_TOOLS)
##MACE_EDIT## 	add_subdirectory(util)
##MACE_EDIT## endif()
##MACE_EDIT## 
##MACE_EDIT## if (YAML_CPP_CLANG_FORMAT_EXE)
##MACE_EDIT##   add_custom_target(format
##MACE_EDIT##     COMMAND clang-format --style=file -i $<TARGET_PROPERTY:yaml-cpp,SOURCES>
##MACE_EDIT##     COMMAND_EXPAND_LISTS
##MACE_EDIT##     COMMENT "Running clang-format"
##MACE_EDIT##     VERBATIM)
##MACE_EDIT## endif()
