function(mace_download_small_file SRC_URL DEST_PATH)
    # check param
    if(NOT IS_ABSOLUTE "${DEST_PATH}")
        message(FATAL_ERROR "Parameter DEST_PATH needs to be an absolute path. (Current value: ${DEST_PATH})")
    endif()
    if(IS_DIRECTORY "${DEST_PATH}")
        message(FATAL_ERROR "Parameter DEST_PATH cannot be a directory. (Current value: ${DEST_PATH})")
    endif()
    # skip if exist
    if(EXISTS "${DEST_PATH}")
        message(STATUS "Reusing ${DEST_PATH}, skpping download")
    else()
        # mkdir
        cmake_path(GET DEST_PATH PARENT_PATH DEST_DIR)
        make_directory("${DEST_DIR}")
        if(NOT IS_DIRECTORY "${DEST_DIR}")
            message(FATAL_ERROR "The parent path of DEST_PATH (${DEST_DIR}) is not a directory.")
        endif()
        # request head
        message(STATUS "Executing command: curl -I -L -s -o \"${DEST_PATH}.head\" \"${SRC_URL}\"")
        execute_process(COMMAND "curl" "-I" "-L" "-s" "-o" "${DEST_PATH}.head" "${SRC_URL}"
                        RESULT_VARIABLE CURL_RETURN)
        # check return
        if(${CURL_RETURN} EQUAL 0)
            # rm head
            file(REMOVE "${DEST_PATH}.head")
            # download
            message(STATUS "Executing command: curl -L -o \"${DEST_PATH}\" \"${SRC_URL}\"")
            execute_process(COMMAND "curl" "-L" "-J" "-o" "${DEST_PATH}" "${SRC_URL}"
                            RESULT_VARIABLE CURL_RETURN)
            # check return
            if(NOT ${CURL_RETURN} EQUAL 0)
                message(SEND_ERROR "Failed to download from ${SRC_URL} to ${DEST_PATH}")
            endif()
        else()
            message(SEND_ERROR "Failed to download from ${SRC_URL} to ${DEST_PATH}")
        endif()
    endif()
endfunction()
