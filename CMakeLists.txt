cmake_minimum_required(VERSION 3.6)

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

set(PROJECT_NAME osxclean-meta)
project(${PROJECT_NAME})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/lib CACHE PATH "Single Directory for all")

option(BUILD_SHARED_LIBS OFF)
set(Boost_USE_STATIC_LIBS ON)

include_directories("./externals/cxx-prettyprint")

enable_testing()

#add_subdirectory( osxclean )
add_subdirectory( uninstaller )
