###########################################################
#
# CMakeLists: Project Drive Manager Libraries
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

#add_subdirectory("Imported")
add_subdirectory("Imported/LoggerLib")
add_subdirectory("Imported/VersionLib")
add_subdirectory("Imported/ConsoleExtensions")