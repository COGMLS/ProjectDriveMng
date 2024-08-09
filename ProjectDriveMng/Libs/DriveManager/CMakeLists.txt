###########################################################
#
# CMakeLists: Drive Manager Library
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
	add_compile_definitions(_WINDOWS)
	add_compile_definitions(_USRDLL)
	add_compile_definitions(_WINDLL)
endif()

if(DebugProjectDriveMng)
	add_compile_definitions(DEBUG)
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Defined the project:
project(DrvMng VERSION 0.0.1 DESCRIPTION "Drive Manager library.")

###########################################################
#
# Project components an settings:
#
###########################################################

# Include libraries directories source codes:
#include_directories("${ProjectDriveMngRoot}/Libs/<lib>")

# Define to export the library methods if is Windows:
if(WIN32)
	# Add the export here
	#add_compile_definitions(TEMPLATESLIB_EXPORTS)
endif()

# Define the library build properties:
if (WIN32)
	add_library(DrvMng SHARED "dllmain.hpp" "dllmain.cpp")
else()
	add_library(DrvMng SHARED)
endif()

# If necessary, link libraries to this one:
if(DebugProjectDriveMng)
	#target_link_libraries(TemplateConsole ${CMAKE_SOURCE_DIR}/<Path2Solution>/<SolutionDir>/<lib>/Debug/<libfile>.lib)
else()
	#target_link_libraries(TemplateConsole ${CMAKE_SOURCE_DIR}/<Path2Solution>/<SolutionDir>/<lib>/Release/<libfile>.lib)
endif()
