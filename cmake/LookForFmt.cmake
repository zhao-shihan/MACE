message(STATUS "Looking for fmt")

set(MACE_FMT_MINIMUM_REQUIRED 10.1.0)

if(NOT MACE_BUILTIN_FMT)
    find_package(fmt ${MACE_FMT_MINIMUM_REQUIRED} QUIET)
    if(NOT fmt_FOUND)
        set(MACE_BUILTIN_FMT ON)
        message(NOTICE "***Notice: fmt not found (minimum required is ${MACE_FMT_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_FMT")
    endif()
endif()

if(MACE_BUILTIN_FMT)
    message(STATUS "MACE will use built-in fmt")
    # check built-in version
    if(MACE_BUILTIN_FMT_VERSION VERSION_LESS MACE_FMT_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided MACE_BUILTIN_FMT_VERSION is ${MACE_BUILTIN_FMT_VERSION}, which is less than the requirement (${MACE_FMT_MINIMUM_REQUIRED}). Changing to ${MACE_FMT_MINIMUM_REQUIRED}")
        set(MACE_BUILTIN_FMT_VERSION ${MACE_FMT_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(MACE_BUILTIN_FMT_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/fmt-${MACE_BUILTIN_FMT_VERSION}")
    set(MACE_BUILTIN_FMT_URL "https://github.com/fmtlib/fmt/archive/refs/tags/${MACE_BUILTIN_FMT_VERSION}.tar.gz")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${MACE_BUILTIN_FMT_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(fmt SOURCE_DIR "${MACE_BUILTIN_FMT_SRC_DIR}")
        message(STATUS "Reusing fmt source ${MACE_BUILTIN_FMT_SRC_DIR}")
    else()
        FetchContent_Declare(fmt SOURCE_DIR "${MACE_BUILTIN_FMT_SRC_DIR}"
                                 URL "${MACE_BUILTIN_FMT_URL}")
        message(STATUS "fmt will be downloaded from ${MACE_BUILTIN_FMT_URL} to ${MACE_BUILTIN_FMT_SRC_DIR}")
    endif()
    # configure it
    message(STATUS "Downloading (if required) and configuring fmt (version: ${MACE_BUILTIN_FMT_VERSION})")
    FetchContent_MakeAvailable(fmt)
    message(STATUS "Downloading (if required) and configuring fmt (version: ${MACE_BUILTIN_FMT_VERSION}) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_FMT_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/fmt-subbuild")
        message(FATAL_ERROR "It seems that the download of fmt is not successful. You can try to run cmake again, or manually download fmt from ${MACE_BUILTIN_FMT_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree and restart the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_FMT)
    message(STATUS "Looking for fmt - found (version: ${fmt_VERSION})")
else()
    message(STATUS "Looking for fmt - built-in (version: ${MACE_BUILTIN_FMT_VERSION})")
endif()
