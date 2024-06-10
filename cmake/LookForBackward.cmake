message(STATUS "Looking for backward-cpp")

set(MACE_BACKWARD_MINIMUM_REQUIRED 1.6)

if(NOT MACE_BUILTIN_BACKWARD)
    find_package(Backward QUIET)
    if(NOT Backward_FOUND)
        set(MACE_BUILTIN_BACKWARD ON)
        message(NOTICE "***Notice: backward-cpp not found. Turning on MACE_BUILTIN_BACKWARD")
    endif()
endif()

if(MACE_BUILTIN_BACKWARD)
    message(STATUS "MACE will use built-in backward-cpp")
    # check built-in version
    if(MACE_BUILTIN_BACKWARD_VERSION VERSION_LESS MACE_BACKWARD_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided MACE_BUILTIN_BACKWARD_VERSION is ${MACE_BUILTIN_BACKWARD_VERSION}, which is less than the requirement (${MACE_BACKWARD_MINIMUM_REQUIRED}). Changing to ${MACE_BACKWARD_MINIMUM_REQUIRED}")
        set(MACE_BUILTIN_BACKWARD_VERSION ${MACE_BACKWARD_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(MACE_BUILTIN_BACKWARD_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/backward-cpp-${MACE_BUILTIN_BACKWARD_VERSION}")
    set(MACE_BUILTIN_BACKWARD_URL "https://github.com/bombela/backward-cpp/archive/refs/tags/v${MACE_BUILTIN_BACKWARD_VERSION}.tar.gz")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${MACE_BUILTIN_BACKWARD_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(Backward SOURCE_DIR "${MACE_BUILTIN_BACKWARD_SRC_DIR}")
        message(STATUS "Reusing backward-cpp source ${MACE_BUILTIN_BACKWARD_SRC_DIR}")
    else()
        FetchContent_Declare(Backward SOURCE_DIR "${MACE_BUILTIN_BACKWARD_SRC_DIR}"
                                      URL "${MACE_BUILTIN_BACKWARD_URL}")
        message(STATUS "backward-cpp will be downloaded from ${MACE_BUILTIN_BACKWARD_URL} to ${MACE_BUILTIN_BACKWARD_SRC_DIR}")
    endif()
    # set options
    set(BACKWARD_SHARED ${BUILD_SHARED_LIBS} CACHE INTERNAL "")
    set(BACKWARD_TESTS OFF CACHE INTERNAL "")
    # configure it
    message(STATUS "Downloading (if required) and configuring backward-cpp (version: ${MACE_BUILTIN_BACKWARD_VERSION})")
    FetchContent_MakeAvailable(Backward)
    message(STATUS "Downloading (if required) and configuring backward-cpp (version: ${MACE_BUILTIN_BACKWARD_VERSION}) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_BACKWARD_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/backward-build")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/backward-subbuild")
        message(FATAL_ERROR "It seems that the download of backward-cpp is not successful. You can try to run cmake again, or manually download backward-cpp from ${MACE_BUILTIN_BACKWARD_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree and restart the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_BACKWARD)
    message(STATUS "Looking for backward-cpp - found")
else()
    message(STATUS "Looking for backward-cpp - built-in (version: ${MACE_BUILTIN_BACKWARD_VERSION})")
endif()
