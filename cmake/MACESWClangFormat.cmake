find_program(CLANG_FORMAT_EXE clang-format)
if(NOT CLANG_FORMAT_EXE)
    set(MACE_CLANG_FORMAT OFF)
    message(NOTICE "***Notice: clang-format not found. For the time turning off MACE_CLANG_FORMAT")
endif()

if(MACE_CLANG_FORMAT)
    file(GLOB_RECURSE MACESW_ALL_SOURCE_FILE_LIST ${MACE_PROJECT_SOURCE_DIR}/*.c++
                                                ${MACE_PROJECT_SOURCE_DIR}/*.h++
                                                ${MACE_PROJECT_SOURCE_DIR}/*.inl
                                                ${MACE_PROJECT_ROOT_DIR}/MACE.c++)
    add_custom_target(macesw-clang-format-check ALL
        ${CLANG_FORMAT_EXE}
            --fail-on-incomplete-format
            --style=file:${MACE_PROJECT_ROOT_DIR}/.clang-format
            --dry-run
            $<$<BOOL:${MACE_CLANG_FORMAT_WERROR}>:--Werror>
            ${MACESW_ALL_SOURCE_FILE_LIST}
        COMMENT "Checking MACESW source code format with ${CLANG_FORMAT_EXE}"
        VERBATIM
        COMMAND_EXPAND_LISTS)
    if(MACE_CLANG_FORMAT_WERROR)
        message(STATUS "MACESW source code format will be checked by ${CLANG_FORMAT_EXE} (warnings as errors)")
    else()
        message(STATUS "MACESW source code format will be checked by ${CLANG_FORMAT_EXE}")
    endif()
else()
    message(WARNING "MACESW source code format will not be checked by clang-format")
endif()
