cmake_minimum_required(VERSION 3.15)

project(sfl
	LANGUAGES
		CXX
)

set(SFL_ROOT_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(SFL_ROOT_PROJECT ON)
endif()

# Build configuration
option(SFL_BUILD_TESTS
    "Build the tests"
    ${SFL_ROOT_PROJECT})

# Library
add_library(sfl INTERFACE)
add_library(sfl::sfl ALIAS sfl)

target_include_directories(sfl INTERFACE
	include
)

set_property(TARGET sfl PROPERTY CXX_STANDARD 11)

# Tests
if (SFL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()
