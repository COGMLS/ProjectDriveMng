###########################################################
#
# CMakeLists: Project Drive Manager Console
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

if(DebugProjectDriveMng)
	add_compile_definitions(DEBUG)
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Defined the project:
project(ProjectDriveConsole VERSION 0.0.1 DESCRIPTION "Console for Project Drive Manager.")

###########################################################
#
# Project components an settings:
#
###########################################################

# Include libraries directories source codes:
#include_directories("${ProjectDriveMngRoot}/Libs/<lib>")

# Define the executable properties:
add_executable(ProjectDriveConsole "main.cpp")

# Link libraries:
#target_link_libraries(ProjectDriveConsole <libname>)

# Link libraries manually if some problem occur
if(DebugProjectDriveMng)
	#target_link_libraries(ProjectDriveConsole ${CMAKE_SOURCE_DIR}/build/<Path2SolutionDir>/<SolutionDir>/<lib>/Debug/<libfile>.lib)
else()
	#target_link_libraries(ProjectDriveConsole ${CMAKE_SOURCE_DIR}/build/<Path2SolutionDir>/<SolutionDir>/<lib>/Release/<libfile>.lib)
endif()