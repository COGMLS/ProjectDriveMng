###########################################################
#
# CMakeLists: Project Drive Manager Imported Libraries
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
			ProjectDriveMngImportedLibs
			VERSION 1.0.0
			DESCRIPTION "Project Drive Manager imported libraries."
		)

###########################################################
#
# Sub projects:
#
###########################################################

add_subdirectory("LoggerLib")
add_subdirectory("VersionLib");