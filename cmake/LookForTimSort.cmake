message(STATUS "Looking for timsort")

set(MACE_TIMSORT_MINIMUM_REQUIRED 3.0.0)

if(NOT MACE_BUILTIN_TIMSORT)
    find_package(timsort ${MACE_TIMSORT_MINIMUM_REQUIRED} QUIET)
    if(NOT timsort_FOUND)
        set(MACE_BUILTIN_TIMSORT ON)
        message(NOTICE "***Notice: timsort not found (minimum required is ${MACE_TIMSORT_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_TIMSORT")
    endif()
endif()

if(MACE_BUILTIN_TIMSORT)
    message(STATUS "MACE will use built-in timsort")
    # check built-in version
    if(MACE_BUILTIN_TIMSORT_VERSION VERSION_LESS MACE_TIMSORT_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided MACE_BUILTIN_TIMSORT_VERSION is ${MACE_BUILTIN_TIMSORT_VERSION}, which is less than the requirement (${MACE_TIMSORT_MINIMUM_REQUIRED}). Changing to ${MACE_TIMSORT_MINIMUM_REQUIRED}")
        set(MACE_BUILTIN_TIMSORT_VERSION ${MACE_TIMSORT_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(MACE_BUILTIN_TIMSORT_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/cpp-TimSort-3.x.y")
    set(MACE_BUILTIN_TIMSORT_URL "https://github.com/zhao-shihan/cpp-TimSort/archive/refs/heads/3.x.y.zip")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${MACE_BUILTIN_TIMSORT_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(timsort SOURCE_DIR "${MACE_BUILTIN_TIMSORT_SRC_DIR}")
        message(STATUS "Reusing timsort source ${MACE_BUILTIN_TIMSORT_SRC_DIR}")
    else()
        FetchContent_Declare(timsort SOURCE_DIR "${MACE_BUILTIN_TIMSORT_SRC_DIR}"
                                      URL "${MACE_BUILTIN_TIMSORT_URL}")
        message(STATUS "timsort will be downloaded from ${MACE_BUILTIN_TIMSORT_URL} to ${MACE_BUILTIN_TIMSORT_SRC_DIR}")
    endif()
    # configure it
    message(STATUS "Downloading (if required) and configuring timsort (version: ${MACE_BUILTIN_TIMSORT_VERSION})")
    FetchContent_MakeAvailable(timsort)
    message(STATUS "Downloading (if required) and configuring timsort (version: ${MACE_BUILTIN_TIMSORT_VERSION}) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_TIMSORT_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/timsort-build")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/timsort-subbuild")
        message(FATAL_ERROR "It seems that the download of timsort is not successful. You can try to run cmake again, or manually download timsort from ${MACE_BUILTIN_TIMSORT_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree and restart the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_TIMSORT)
    message(STATUS "Looking for timsort - found (version: ${timsort_VERSION})")
else()
    message(STATUS "Looking for timsort - built-in (version: ${MACE_BUILTIN_TIMSORT_VERSION})")
endif()
