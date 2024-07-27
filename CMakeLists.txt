cmake_minimum_required(VERSION 3.10)

# Set the project name
project(mobi_test VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the executable for the main project
file(GLOB MAIN_SOURCES "src/*.cpp")
add_executable(mobi_test ${MAIN_SOURCES})


add_compile_definitions(PROJECT_NAME="${PROJECT_NAME}")

# If you want to build tests later, you can add this back in.
# # Add the executable for the tests
# file(GLOB TEST_SOURCES "tests/*.cpp src/sample.cpp")  # Include src/sample.cpp here
# add_executable(mobi_test_tests ${TEST_SOURCES})

# Link libraries if any (add them here if needed)
# target_link_libraries(mobi_test <library_name>)
