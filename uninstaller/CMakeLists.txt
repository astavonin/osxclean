cmake_minimum_required(VERSION 3.7)

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

set(PROJECT_NAME uninstaller)
project(${PROJECT_NAME})

find_package(Boost COMPONENTS
    filesystem
    REQUIRED)

set(${PROJECT_NAME}_sources
    src/uninstaller_impl.cpp
    src/plist.mm)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_sources})
target_link_libraries(${PROJECT_NAME} ${Boost_FILESYSTEM_LIBRARY}
    "-framework Foundation")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src ${Boost_INCLUDE_DIRS})

install(TARGETS ${PROJECT_NAME}
    ARCHIVE  DESTINATION lib
    LIBRARY  DESTINATION lib
    RUNTIME  DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)

export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}-Config.cmake)

enable_testing()

add_subdirectory(test)
