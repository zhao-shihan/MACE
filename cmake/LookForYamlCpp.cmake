message(STATUS "Looking for yaml-cpp")

set(MACE_YAML_CPP_MINIMUM_REQUIRED 0.6.0)

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
    # set download src and dest
    include(FetchContent)
    set(MACE_BUILTIN_YAML_CPP_DIR "${MACE_PROJECT_3RDPARTY_DIR}/yaml-cpp-yaml-cpp-${MACE_BUILTIN_YAML_CPP_VERSION}")
    set(MACE_BUILTIN_YAML_CPP_URL "https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-${MACE_BUILTIN_YAML_CPP_VERSION}.tar.gz")
    if(EXISTS "${MACE_BUILTIN_YAML_CPP_DIR}/CMakeLists.txt")
        message(STATUS "Reusing yaml-cpp source ${MACE_BUILTIN_YAML_CPP_DIR}")
        FetchContent_Declare(yaml-cpp SOURCE_DIR "${MACE_BUILTIN_YAML_CPP_DIR}")
    else()
        message(STATUS "Fetching yaml-cpp from ${MACE_BUILTIN_YAML_CPP_URL} to ${MACE_BUILTIN_YAML_CPP_DIR}")
        FetchContent_Declare(yaml-cpp SOURCE_DIR "${MACE_BUILTIN_YAML_CPP_DIR}"
                                      URL "${MACE_BUILTIN_YAML_CPP_URL}")
    endif()
    # configure it
    message(STATUS ">>>>>>>> Configuring built-in yaml-cpp (version: ${MACE_BUILTIN_YAML_CPP_VERSION})")
    FetchContent_MakeAvailable(yaml-cpp)
    message(STATUS "<<<<<<<< Configuring built-in yaml-cpp (version: ${MACE_BUILTIN_YAML_CPP_VERSION}) - done")
endif()

if(NOT MACE_BUILTIN_YAML_CPP)
    message(STATUS "Looking for yaml-cpp - found (version: ${yaml-cpp_VERSION})")
else()
    message(STATUS "Looking for yaml-cpp - built-in (version: ${MACE_BUILTIN_YAML_CPP_VERSION})")
endif()
