message(STATUS "Looking for EFM")

set(MACE_EFM_MINIMUM_REQUIRED 0.0.1)

if(NOT MACE_BUILTIN_EFM)
    find_package(EFM ${MACE_EFM_MINIMUM_REQUIRED} QUIET)
    if(NOT EFM_FOUND)
        set(MACE_BUILTIN_EFM ON)
        message(NOTICE "***Notice: EFM not found (minimum required is ${MACE_EFM_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_EFM")
    endif()
endif()

if(MACE_BUILTIN_EFM)
    message(STATUS "MACE will use built-in EFM")
    # check built-in version
    if(MACE_BUILTIN_EFM_VERSION VERSION_LESS MACE_EFM_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided MACE_BUILTIN_EFM_VERSION is ${MACE_BUILTIN_EFM_VERSION}, which is less than the requirement (${MACE_EFM_MINIMUM_REQUIRED}). Changing to ${MACE_EFM_MINIMUM_REQUIRED}")
        set(MACE_BUILTIN_EFM_VERSION ${MACE_EFM_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(MACE_BUILTIN_EFM_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/EFM-main")
    set(MACE_BUILTIN_EFM_URL "https://github.com/zhao-shihan/EFM/archive/refs/heads/main.zip")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${MACE_BUILTIN_EFM_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(EFM SOURCE_DIR "${MACE_BUILTIN_EFM_SRC_DIR}")
        message(STATUS "Reusing EFM source ${MACE_BUILTIN_EFM_SRC_DIR}")
    else()
        FetchContent_Declare(EFM SOURCE_DIR "${MACE_BUILTIN_EFM_SRC_DIR}"
                                 URL "${MACE_BUILTIN_EFM_URL}")
        message(STATUS "EFM will be downloaded from ${MACE_BUILTIN_EFM_URL} to ${MACE_BUILTIN_EFM_SRC_DIR}")
    endif()
    # set options
    set(EFM_INSTALL ON CACHE INTERNAL "")
    # configure it
    message(STATUS "Downloading (if required) and configuring EFM (version: ${MACE_BUILTIN_EFM_VERSION})")
    FetchContent_MakeAvailable(EFM)
    message(STATUS "Downloading (if required) and configuring EFM (version: ${MACE_BUILTIN_EFM_VERSION}) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_EFM_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/efm-build")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/efm-subbuild")
        message(FATAL_ERROR "It seems that the download of EFM is not successful. You can try to run cmake again, or manually download EFM from ${MACE_BUILTIN_EFM_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree and restart the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_EFM)
    message(STATUS "Looking for EFM - found (version: ${EFM_VERSION})")
else()
    message(STATUS "Looking for EFM - built-in (version: ${MACE_BUILTIN_EFM_VERSION})")
endif()
