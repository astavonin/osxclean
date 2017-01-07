set(PROJECT_NAME uninstaller_unit_tests)
project(${PROJECT_NAME})

find_package (Boost COMPONENTS unit_test_framework system filesystem REQUIRED)

set(${PROJECT_NAME}_source
    plist_tests.cpp
    uninstaller_base_tests.cpp
    app_uninstaller_tests.cpp
    main.cpp
    )

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_source})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${Boost_INCLUDE_DIRS}
    "../src")
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} uninstaller)

add_test(NAME ${PROJECT_NAME}-Tests COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set_property(TEST ${PROJECT_NAME}-Tests PROPERTY LABELS "unit")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_LIST_DIR}/test_data
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data
    )
