message(STATUS "Looking for yaml-cpp")

set(MACE_YAML_CPP_MINIMUM_REQUIRED 0.8.0)

if(NOT MACE_BUILTIN_YAML_CPP)
    find_package(yaml-cpp ${MACE_YAML_CPP_MINIMUM_REQUIRED} QUIET)
    if(NOT yaml-cpp_FOUND)
        set(MACE_BUILTIN_YAML_CPP ON)
        message(NOTICE "***Notice: yaml-cpp not found (minimum required is ${MACE_YAML_CPP_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_YAML_CPP")
    endif()
endif()

if(MACE_BUILTIN_YAML_CPP)
    message(STATUS "MACE will use built-in yaml-cpp")
    # check built-in version
    if(MACE_BUILTIN_YAML_CPP_VERSION VERSION_LESS MACE_YAML_CPP_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided MACE_BUILTIN_YAML_CPP_VERSION is ${MACE_BUILTIN_YAML_CPP_VERSION}, which is less than the requirement (${MACE_YAML_CPP_MINIMUM_REQUIRED}). Changing to ${MACE_YAML_CPP_MINIMUM_REQUIRED}")
        set(MACE_BUILTIN_YAML_CPP_VERSION ${MACE_YAML_CPP_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(MACE_BUILTIN_YAML_CPP_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/yaml-cpp-${MACE_BUILTIN_YAML_CPP_VERSION}")
    set(MACE_BUILTIN_YAML_CPP_URL "https://github.com/jbeder/yaml-cpp/archive/refs/tags/${MACE_BUILTIN_YAML_CPP_VERSION}.tar.gz")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${MACE_BUILTIN_YAML_CPP_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(yaml-cpp SOURCE_DIR "${MACE_BUILTIN_YAML_CPP_SRC_DIR}")
        message(STATUS "Reusing yaml-cpp source ${MACE_BUILTIN_YAML_CPP_SRC_DIR}")
    else()
        FetchContent_Declare(yaml-cpp SOURCE_DIR "${MACE_BUILTIN_YAML_CPP_SRC_DIR}"
                                      URL "${MACE_BUILTIN_YAML_CPP_URL}")
        message(STATUS "yaml-cpp will be downloaded from ${MACE_BUILTIN_YAML_CPP_URL} to ${MACE_BUILTIN_YAML_CPP_SRC_DIR}")
    endif()
    # set options
    set(YAML_CPP_BUILD_CONTRIB ON)
    set(YAML_CPP_BUILD_TOOLS ON)
    set(YAML_BUILD_SHARED_LIBS OFF)
    set(YAML_CPP_INSTALL ON)
    set(YAML_CPP_FORMAT_SOURCE OFF)
    set(YAML_CPP_BUILD_TESTS OFF)
    set(YAML_MSVC_SHARED_RT ${MACE_USE_SHARED_MSVC_RT})
    # configure it
    message(STATUS "Downloading (if required) and configuring yaml-cpp (version: ${MACE_BUILTIN_YAML_CPP_VERSION})")
    FetchContent_MakeAvailable(yaml-cpp)
    message(STATUS "Downloading (if required) and configuring yaml-cpp (version: ${MACE_BUILTIN_YAML_CPP_VERSION}) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_YAML_CPP_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/yaml-cpp-subbuild")
        message(FATAL_ERROR "It seems that the download of yaml-cpp is not successful. You can try to run cmake again, or manually download yaml-cpp from ${MACE_BUILTIN_YAML_CPP_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree and restart the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_YAML_CPP)
    message(STATUS "Looking for yaml-cpp - found (version: ${yaml-cpp_VERSION})")
else()
    message(STATUS "Looking for yaml-cpp - built-in (version: ${MACE_BUILTIN_YAML_CPP_VERSION})")
endif()
