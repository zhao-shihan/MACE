message(STATUS "Looking for mace_test_data")

set(MACE_MACE_TEST_DATA_MINIMUM_REQUIRED 0.25.10140055)

if(NOT MACE_BUILTIN_MACE_TEST_DATA)
    find_package(mace_test_data ${MACE_MACE_TEST_DATA_MINIMUM_REQUIRED})
    if(NOT mace_test_data_FOUND)
        set(MACE_BUILTIN_MACE_TEST_DATA ON)
        message(NOTICE "***Notice: mace_test_data not found (minimum required is ${MACE_MACE_TEST_DATA_MINIMUM_REQUIRED}). For the time turning on MACE_BUILTIN_MACE_TEST_DATA")
    endif()
endif()

if(MACE_BUILTIN_MACE_TEST_DATA)
    message(STATUS "MACE will use built-in mace_test_data")
    # check built-in version
    if(MACE_BUILTIN_MACE_TEST_DATA_VERSION VERSION_LESS MACE_MACE_TEST_DATA_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided MACE_BUILTIN_MACE_TEST_DATA_VERSION is ${MACE_BUILTIN_MACE_TEST_DATA_VERSION}, which is less than the requirement (${MACE_MACE_TEST_DATA_MINIMUM_REQUIRED}). Changing to ${MACE_MACE_TEST_DATA_MINIMUM_REQUIRED}")
        set(MACE_BUILTIN_MACE_TEST_DATA_VERSION ${MACE_MACE_TEST_DATA_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(MACE_BUILTIN_MACE_TEST_DATA_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/mace_test_data-v${MACE_MACE_TEST_DATA_MINIMUM_REQUIRED}")
    set(MACE_BUILTIN_MACE_TEST_DATA_URL "https://code.ihep.ac.cn/zhaoshh7/mace_test_data/-/archive/v${MACE_MACE_TEST_DATA_MINIMUM_REQUIRED}/mace_test_data-v${MACE_MACE_TEST_DATA_MINIMUM_REQUIRED}.tar.gz")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${MACE_BUILTIN_MACE_TEST_DATA_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(mace_test_data SOURCE_DIR "${MACE_BUILTIN_MACE_TEST_DATA_SRC_DIR}")
        message(STATUS "Reusing mace_test_data source ${MACE_BUILTIN_MACE_TEST_DATA_SRC_DIR}")
    else()
        FetchContent_Declare(mace_test_data SOURCE_DIR "${MACE_BUILTIN_MACE_TEST_DATA_SRC_DIR}"
                                            URL "${MACE_BUILTIN_MACE_TEST_DATA_URL}")
        message(STATUS "mace_test_data will be downloaded from ${MACE_BUILTIN_MACE_TEST_DATA_URL} to ${MACE_BUILTIN_MACE_TEST_DATA_SRC_DIR}")
    endif()
    # configure it
    message(STATUS "Downloading (if required) and configuring mace_test_data (version: ${MACE_BUILTIN_MACE_TEST_DATA_VERSION})")
    FetchContent_MakeAvailable(mace_test_data)
    message(STATUS "Downloading (if required) and configuring mace_test_data (version: ${MACE_BUILTIN_MACE_TEST_DATA_VERSION}) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_MACE_TEST_DATA_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/mace_test_data-build")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/mace_test_data-subbuild")
        message(FATAL_ERROR "It seems that the download of mace_test_data has failed. You can try running cmake again, or manually download mace_test_data from ${MACE_BUILTIN_MACE_TEST_DATA_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try cleaning the build tree and restarting the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_MACE_TEST_DATA)
    message(STATUS "Looking for mace_test_data - found (version: ${mace_test_data_VERSION})")
else()
    message(STATUS "Looking for mace_test_data - built-in (version: ${MACE_BUILTIN_MACE_TEST_DATA_VERSION})")
endif()
