cmake_minimum_required(VERSION 2.6)
project(str_builder)

include(ExternalProject)

# Set default ExternalProject root directory
# set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/ThirdParty)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

# Specify include dir
include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

# Declare the main str_builder library
add_library(strbuilder strbuilder.c)

# Turn testing on.. OK?
enable_testing()

# Add the test executable which will actually be running all our tests
add_executable(test_strbuilder test_strbuilder.cpp)

# Create dependency of MainTest on googletest - make sure this googletest gets built!
add_dependencies(test_strbuilder googletest)

# Link the main unit test executable against the str_builder library + the googletest library + pthread (required by googletest)
target_link_libraries(test_strbuilder strbuilder gtest gtest_main pthread)

# Add unit test executable as a 'test' so we can just run 'make test'
add_test(test_strbuilder test_strbuilder)




#cmake_minimum_required (VERSION 2.8.11)
#project (test_str_builder)

#include_directories (/tmp/googletest-release-1.8.0/googletest/include)
#link_directories (/tmp/googletest-release-1.8.0/build/googlemock/gtest)

#add_executable (_test_str_builder str_builder.c test_str_builder.cpp)

#target_link_libraries (_test_str_builder gtest gtest_main pthread)
