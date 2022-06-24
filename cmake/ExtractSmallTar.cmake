function(mace_extract_small_tar TAR_PATH DEST_DIR)
    # check param
    if(NOT IS_ABSOLUTE "${TAR_PATH}")
        message(FATAL_ERROR "Parameter TAR_PATH needs to be an absolute path. (Current value: ${TAR_PATH})")
    endif()
    if(IS_DIRECTORY "${TAR_PATH}")
        message(FATAL_ERROR "Parameter TAR_PATH cannot be a directory. (Current value: ${TAR_PATH})")
    endif()
    if(NOT IS_ABSOLUTE "${DEST_DIR}")
        message(FATAL_ERROR "Parameter DEST_DIR needs to be an absolute path. (Current value: ${DEST_DIR})")
    endif()
    # mkdir
    make_directory("${DEST_DIR}")
    if(NOT IS_DIRECTORY "${DEST_DIR}")
        message(FATAL_ERROR "Parameter DEST_DIR needs to be a directory. (Current value: ${DEST_DIR})")
    endif()
    # process tar xf
    message(STATUS "Extracting ${TAR_PATH} to ${DEST_DIR} (\"${CMAKE_COMMAND}\" -E tar xf \"${TAR_PATH}\")")
    execute_process(COMMAND "${CMAKE_COMMAND}" -E tar xf "${TAR_PATH}"
                    WORKING_DIRECTORY "${DEST_DIR}"
                    RESULT_VARIABLE TAR_RETURN)
    # check return
    if(${TAR_RETURN} EQUAL 0)
        message(STATUS "Extraction completed")
    else()
        message(SEND_ERROR "Failed to extract ${TAR_PATH} to ${DEST_DIR}, error: ${TAR_RETURN}")
    endif()
endfunction()
