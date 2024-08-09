###########################################################
#
# CMakeLists: Remote Link Selector
#
###########################################################

cmake_minimum_required(VERSION 3.28)

###########################################################
#
# Define the general solution settings
#
###########################################################

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define if is Windows Environment:

if(WIN32)
	add_compile_definitions(WIN32)
endif()

if(WIN32)
	add_compile_definitions(_CONSOLE)
endif()

if(DebugRemoteLinkSelHelper)
	add_compile_definitions(DEBUG)
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Defined the project:
project(RemoteLinkSelector VERSION 0.0.1 DESCRIPTION "Tool to select an specific destination for symbolic link that can change it's reference to a remote git server.")

###########################################################
#
# Project components an settings:
#
###########################################################

# Include libraries directories source codes:
#include_directories("${RemoteLinkSelRoot}/Libs/<lib>")

# Define the executable properties:
add_executable(
				RemoteLinkSel # Application's name
				"main.cpp"
				"definitions.hpp"
				"directory.hpp" "directory.cpp"
				"places.hpp" "places.cpp"
				"config.hpp" "config.cpp"
				)

#target_link_libraries(RemoteLinkSelector <libName>)
