###########################################################
#
# CMakeLists: Archive Libraries
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

# Define local libraries root var:
set(ProjectDriveMngLibsRoot ${CMAKE_CURRENT_LIST_DIR})

project(
			ProjectDriveMngLibs
			VERSION 0.0.1
			DESCRIPTION "Project Drive Manager libraries."
		)

###########################################################
#
# Sub projects:
#
###########################################################

add_subdirectory("Imported")
#add_subdirectory("Imported/LoggerLib")
#add_subdirectory("Imported/VersionLib")
#add_subdirectory("Imported/ConsoleExtensions")
add_subdirectory("MngConfig")
add_subdirectory("ArcDrive")