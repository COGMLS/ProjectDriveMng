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

if(DebugProjectDriveMng OR DebugSolution)
	add_compile_definitions(DEBUG)
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Defined the project:
project(
			ProjectDriveMng
			VERSION 0.0.1
			DESCRIPTION "Project Drive Manager Console"
		)

###########################################################
#
# Project components settings:
#
###########################################################

# Include libraries directories source codes:
#include_directories("${ReposRoot}/Libs/<lib>")

# Define the executable properties:
add_executable(
					ProjectDriveMng
					"main.cpp"
				)

# Define manual library link:
set(UseManualTargetLinkLibs False)
				
# Link the VersionLib:
if(UseManualTargetLinkLibs)
	if (WIN32)
		if(DebugProjectDriveMng)
			#target_link_libraries(ProjectDriveMng ${ReposRoot}/build/VersionLib/Libs/<lib>/Debug/VersionLib.lib)
		else()
			#target_link_libraries(ProjectDriveMng ${ReposRoot}/build/VersionLib/Libs/<lib>/Release/VersionLib.lib)
		endif()
	else()
		#target_link_libraries(ProjectDriveMng ${ReposRoot}/build/bin/libVersionLib.so)
	endif()
else()
	target_link_libraries(ProjectDriveMng VersionLib)
	target_link_libraries(ProjectDriveMng LoggerLib)
endif()