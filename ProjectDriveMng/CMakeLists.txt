###########################################################
#
# CMakeLists: Project Drive Manager Solution
#
###########################################################

cmake_minimum_required(VERSION 3.28)

###########################################################
#
# Define the general solution settings
#
###########################################################

# Define current project base working directory location:
set(ProjectDriveMngRoot ${CMAKE_CURRENT_LIST_DIR})

# Define if will set the project debug definition:
set(DebugProjectDriveMng True)

# Define if is Windows Environment:

if(WIN32)
	add_compile_definitions(WIN32)
endif()

if(DebugProjectDriveMng)
	add_compile_definitions(DEBUG)
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

project(ProjectDriveMng VERSION 0.0.1 DESCRIPTION "Project Drive Manager")

###########################################################
#
# Sub projects:
#
###########################################################

add_subdirectory("Console")