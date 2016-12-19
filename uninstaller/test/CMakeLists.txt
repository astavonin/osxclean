set(PROJECT_NAME uninstaller_unit_tests)
project(${PROJECT_NAME})

find_package (Boost COMPONENTS unit_test_framework system filesystem REQUIRED)

set(${PROJECT_NAME}_source
    base_tests.cpp
    main.cpp
    )

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_source})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} uninstaller)

add_test(NAME ${PROJECT_NAME}-Tests COMMAND ${PROJECT_NAME})
set_property(TEST ${PROJECT_NAME}-Tests PROPERTY LABELS "unit")

