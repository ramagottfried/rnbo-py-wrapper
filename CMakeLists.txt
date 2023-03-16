cmake_minimum_required(VERSION 3.10)

# Set the C++ standard to at least C++11, which is needed for RNBO
set (CMAKE_CXX_STANDARD 17)

set (CMAKE_BUILD_TYPE Release)

# Set the project name
project(RNBOExportLib)

set(RNBO_EXPORT_SRC_FILE "rnbo_source.cpp")

if(DEFINED RNBO_EXPORT_FOLDER)
    
    if(NOT IS_ABSOLUTE ${RNBO_EXPORT_FOLDER})
        set(RNBO_EXPORT_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/${RNBO_EXPORT_FOLDER}")
    endif()

    message(STATUS "RNBO Folder: ${RNBO_EXPORT_FOLDER}")
    message(STATUS "Bulding RNBO Export Source File: ${RNBO_EXPORT_SRC_FILE}")

    # Add the main executable as well as the RNBO sources
    add_library(RNBOExportLib SHARED rnbo-lib-wrapper.cpp "${RNBO_EXPORT_FOLDER}/${RNBO_EXPORT_SRC_FILE}" "${RNBO_EXPORT_FOLDER}/rnbo/RNBO.cpp")

    # Include the RNBO headers
    include_directories(RNBOExportLib PRIVATE "${RNBO_EXPORT_FOLDER}/rnbo" "${RNBO_EXPORT_FOLDER}/rnbo/common")

    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/rnbo.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/import-test.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

else()
    message(FATAL_ERROR "Needs RNBO folder path, e.g. -DRNBO_EXPORT_FOLDER=../rnbo-export")
endif()
