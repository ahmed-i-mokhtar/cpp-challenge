# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(CSVProcessor VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source files
set(SOURCES
    main.cpp
    # Add other source files here if needed
)

# Specify the header files
set(HEADERS
    solution.h
)

# Define the executable for the main program
add_executable(csv_processor ${SOURCES})

# Include GoogleTest
# Find the package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Define unit test source files
set(TEST_SOURCES
    test.cpp
    # Add other test files here if needed
)

# Define the executable for the unit tests
add_executable(runTests ${TEST_SOURCES})

# Link GoogleTest and pthread libraries to the test executable
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

# Link the main program with required libraries
# You can link libraries here if needed

# Add a custom target to build and run the tests
add_custom_target(run_tests
    COMMAND runTests
    DEPENDS runTests
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    COMMENT "Running unit tests"
)

# Optionally, add the following to enable automatic testing with CTest
enable_testing()
add_test(NAME CSVProcessorTests COMMAND runTests)
