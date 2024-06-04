message(STATUS "Looking for Microsoft.GSL")

set(MACE_MSGSL_MINIMUM_REQUIRED 4.0.0)

if(NOT MACE_BUILTIN_MSGSL)
    find_package(Microsoft.GSL ${MACE_MSGSL_MINIMUM_REQUIRED} QUIET)
    if(NOT Microsoft.GSL_FOUND)
        set(MACE_BUILTIN_MSGSL ON)
        message(NOTICE "***Notice: Microsoft.GSL not found (minimum required is ${MACE_MSGSL_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_MSGSL")
    endif()
endif()

if(MACE_BUILTIN_MSGSL)
    message(STATUS "MACE will use built-in Microsoft.GSL")
    # check built-in version
    if(MACE_BUILTIN_MSGSL_VERSION VERSION_LESS MACE_MSGSL_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided MACE_BUILTIN_MSGSL_VERSION is ${MACE_BUILTIN_MSGSL_VERSION}, which is less than the requirement (${MACE_MSGSL_MINIMUM_REQUIRED}). Changing to ${MACE_MSGSL_MINIMUM_REQUIRED}")
        set(MACE_BUILTIN_MSGSL_VERSION ${MACE_MSGSL_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(MACE_BUILTIN_MSGSL_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/GSL-${MACE_BUILTIN_MSGSL_VERSION}")
    set(MACE_BUILTIN_MSGSL_URL "https://github.com/microsoft/GSL/archive/refs/tags/v${MACE_BUILTIN_MSGSL_VERSION}.tar.gz")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${MACE_BUILTIN_MSGSL_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(MSGSL SOURCE_DIR "${MACE_BUILTIN_MSGSL_SRC_DIR}")
        message(STATUS "Reusing Microsoft.GSL source ${MACE_BUILTIN_MSGSL_SRC_DIR}")
    else()
        FetchContent_Declare(MSGSL SOURCE_DIR "${MACE_BUILTIN_MSGSL_SRC_DIR}"
                                   URL "${MACE_BUILTIN_MSGSL_URL}")
        message(STATUS "Microsoft.GSL will be downloaded from ${MACE_BUILTIN_MSGSL_URL} to ${MACE_BUILTIN_MSGSL_SRC_DIR}")
    endif()
    # set options
    set(GSL_INSTALL ON CACHE INTERNAL "")
    # configure it
    message(STATUS "Downloading (if required) and configuring Microsoft.GSL (version: ${MACE_BUILTIN_MSGSL_VERSION})")
    FetchContent_MakeAvailable(MSGSL)
    message(STATUS "Downloading (if required) and configuring Microsoft.GSL (version: ${MACE_BUILTIN_MSGSL_VERSION}) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_MSGSL_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/msgsl-subbuild")
        message(FATAL_ERROR "It seems that the download of Microsoft.GSL is not successful. You can try to run cmake again, or manually download Microsoft.GSL from ${MACE_BUILTIN_MSGSL_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree and restart the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_MSGSL)
    message(STATUS "Looking for Microsoft.GSL - found (version: ${Microsoft.GSL_VERSION})")
else()
    message(STATUS "Looking for Microsoft.GSL - built-in (version: ${MACE_BUILTIN_MSGSL_VERSION})")
endif()
