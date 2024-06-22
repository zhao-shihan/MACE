message(STATUS "Looking for GenFit")

set(MACE_GENFIT_MINIMUM_REQUIRED 2.2.0)

if(NOT MACE_BUILTIN_GENFIT)
    find_package(genfit ${MACE_GENFIT_MINIMUM_REQUIRED})
    if(NOT genfit_FOUND)
        set(MACE_BUILTIN_GENFIT ON)
        message(NOTICE "***Notice: GenFit not found (minimum required is ${MACE_GENFIT_MINIMUM_REQUIRED}). Turning on MACE_BUILTIN_GENFIT")
    endif()
endif()

if(MACE_BUILTIN_GENFIT)
    message(STATUS "MACE will use built-in GenFit")
    # set download dest and URL
    set(MACE_BUILTIN_GENFIT_SRC_DIR "${MACE_PROJECT_3RDPARTY_DIR}/GenFit-02-00-01")
    set(MACE_BUILTIN_GENFIT_URL "https://github.com/zhao-shihan/GenFit/archive/refs/heads/master.zip")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${MACE_BUILTIN_GENFIT_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(genfit SOURCE_DIR "${MACE_BUILTIN_GENFIT_SRC_DIR}")
        message(STATUS "Reusing GenFit source ${MACE_BUILTIN_GENFIT_SRC_DIR}")
    else()
        FetchContent_Declare(genfit SOURCE_DIR "${MACE_BUILTIN_GENFIT_SRC_DIR}"
                                    URL "${MACE_BUILTIN_GENFIT_URL}")
        message(STATUS "GenFit will be downloaded from ${MACE_BUILTIN_GENFIT_URL} to ${MACE_BUILTIN_GENFIT_SRC_DIR}")
    endif()
    # set options
    set(GF_BUILD_EVENT_DISPLAY ${MACE_BUILTIN_GENFIT_EVENT_DISPLAY} CACHE INTERNAL "")
    # configure it
    message(STATUS "Downloading (if required) and configuring GenFit (version: 2.2.0)")
    FetchContent_MakeAvailable(genfit)
    message(STATUS "Downloading (if required) and configuring GenFit (version: 2.2.0) - done")
    # check download
    if(NOT EXISTS "${MACE_BUILTIN_GENFIT_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/genfit-build")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/genfit-subbuild")
        message(FATAL_ERROR "It seems that the download of GenFit is not successful. You can try to run cmake again, or manually download GenFit from ${MACE_BUILTIN_GENFIT_URL} and extract it to ${MACE_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try to clean the build tree and restart the build.")
    endif()
endif()

if(NOT MACE_BUILTIN_GENFIT)
    message(STATUS "Looking for GenFit - found (version: ${genfit_VERSION})")
    set(GENFIT_INCLUDE_DIRS "${genfit_DIR}/include")
else()
    message(STATUS "Looking for GenFit - built-in (version: 2.2.0)")
    set(GENFIT_INCLUDE_DIRS "${MACE_BUILTIN_GENFIT_SRC_DIR}/core/include"
                            "${MACE_BUILTIN_GENFIT_SRC_DIR}/eventDisplay/include"
                            "${MACE_BUILTIN_GENFIT_SRC_DIR}/fields/include"
                            "${MACE_BUILTIN_GENFIT_SRC_DIR}/finitePlanes/include"
                            "${MACE_BUILTIN_GENFIT_SRC_DIR}/fitters/include"
                            "${MACE_BUILTIN_GENFIT_SRC_DIR}/GBL/include"
                            "${MACE_BUILTIN_GENFIT_SRC_DIR}/measurements/include"
                            "${MACE_BUILTIN_GENFIT_SRC_DIR}/trackReps/include"
                            "${MACE_BUILTIN_GENFIT_SRC_DIR}/utilities/include")
endif()
