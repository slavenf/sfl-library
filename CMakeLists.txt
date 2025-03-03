cmake_minimum_required(VERSION 3.15)

project(sfl
	LANGUAGES
		CXX
)

add_library(sfl INTERFACE)
add_library(sfl::sfl ALIAS sfl)

target_include_directories(sfl INTERFACE
	include
)

set_property(TARGET sfl PROPERTY CXX_STANDARD 11)

set(SFL_NATVIS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/sfl.natvis")

target_link_options(sfl INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/natvis:${SFL_NATVIS_FILE}>
)

install(
	DIRECTORY
		include/sfl
	DESTINATION
		include
)
