message(STATUS "Looking for muc")

set(MACE_MUC_MINIMUM_REQUIRED 0.0.1)

if(NOT MACE_BUILTIN_MUC)
    find_package(muc ${MACE_MUC_MINIMUM_REQUIRED} QUIET)
    if(NOT muc_FOUND)
        set(MACE_BUILTIN_MUC ON)
        message(NOTICE "***Notice: muc not found (minimum required is ${MACE_MUC_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_MUC")
    endif()
endif()

if(MACE_BUILTIN_MUC)
    message(STATUS "MACE will use built-in muc")
    # # check built-in version
    # if(MACE_BUILTIN_MUC_VERSION VERSION_LESS MACE_MUC_MINIMUM_REQUIRED)
    #     message(NOTICE "***Notice: Provided MACE_BUILTIN_MUC_VERSION is ${MACE_BUILTIN_MUC_VERSION}, which is less than the requirement (${MACE_MUC_MINIMUM_REQUIRED}). Changing to ${MACE_MUC_MINIMUM_REQUIRED}")
    #     set(MACE_BUILTIN_MUC_VERSION ${MACE_MUC_MINIMUM_REQUIRED})
    # endif()
    set(MACE_BUILTIN_MUC_VERSION 0.0.1) # for now we use a hard-coded version
    # set download dest and URL
    set(MACE_BUILTIN_MUC_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/muc-main")
    set(MACE_BUILTIN_MUC_URL "https://github.com/zhao-shihan/muc/archive/refs/heads/main.zip")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${MACE_BUILTIN_MUC_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(muc SOURCE_DIR "${MACE_BUILTIN_MUC_SRC_DIR}")
        message(STATUS "Reusing muc source ${MACE_BUILTIN_MUC_SRC_DIR}")
    else()
        FetchContent_Declare(muc SOURCE_DIR "${MACE_BUILTIN_MUC_SRC_DIR}"
                                      URL "${MACE_BUILTIN_MUC_URL}")
        message(STATUS "muc will be downloaded from ${MACE_BUILTIN_MUC_URL} to ${MACE_BUILTIN_MUC_SRC_DIR}")
    endif()
    # set options
    set(MUC_INSTALL ON CACHE INTERNAL "")
    # configure it
    message(STATUS "Downloading (if required) and configuring muc (version: ${MACE_BUILTIN_MUC_VERSION})")
    FetchContent_MakeAvailable(muc)
    message(STATUS "Downloading (if required) and configuring muc (version: ${MACE_BUILTIN_MUC_VERSION}) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_MUC_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/muc-subbuild")
        message(FATAL_ERROR "It seems that the download of muc is not successful. You can try to run cmake again, or manually download muc from ${MACE_BUILTIN_MUC_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree and restart the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_MUC)
    message(STATUS "Looking for muc - found (version: ${muc_VERSION})")
else()
    message(STATUS "Looking for muc - built-in (version: ${MACE_BUILTIN_MUC_VERSION})")
endif()
