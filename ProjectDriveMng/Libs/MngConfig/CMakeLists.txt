###########################################################
#
# CMakeLists: Manager Configuration Library
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

# Define local Settings Library project root var:
set(ArcConfigMngRoot ${CMAKE_CURRENT_LIST_DIR})

# Define if is Windows Environment:

if(WIN32)
	add_compile_definitions(WIN32)
	add_compile_definitions(_WINDOWS)
	add_compile_definitions(_USRDLL)
	add_compile_definitions(_WINDLL)
endif()

if (DebugSolution AND NOT DebugMngConfigLib)
	set(DebugMngConfigLib True)
endif()

if(DebugMngConfigLib)
	add_compile_definitions(DEBUG)
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Define the project:
project(
			MngConfig
			VERSION 0.0.1
			DESCRIPTION "Manager Configuration Library for Project Drive Manager"
		)

###########################################################
#
# Project components settings:
#
###########################################################

# Include libraries directories source codes:
#include_directories("${ReposRoot}/Libraries/<lib>")
include_directories("${ArcConfigMngRoot}")
include_directories("${ArcConfigMngRoot}/Config")
include_directories("${ProjectDriveMngLibsRoot}/Imported/VersionLib")

# Define to export the library methods if is Windows:
if(WIN32)
	# Add the export here
	add_compile_definitions(ARC_CONFIG_LIB_EXPORTS)
endif()

if (WIN32)
	add_library(
					MngConfig
					SHARED
					"dllmain.hpp" "dllmain.cpp"
					# Config library part:
					"Config/ArcConfig.hpp" "Config/ArcConfig.cpp"
					"Config/ArcConfigTools.hpp" "Config/ArcConfigTools.cpp"
					"Config/ArcDriveConfig.hpp"
					"Config/ConfigData.hpp" "Config/ConfigData.cpp"
					"Config/Datatypes.hpp"
					# Manager Config:
					"MngConfig.hpp"
					"MngConfigVersion.hpp"
				)
else()
	add_library(
					MngConfig
					SHARED
					# Config library part:
					"Config/ArcConfig.hpp" "Config/ArcConfig.cpp"
					"Config/ArcConfigTools.hpp" "Config/ArcConfigTools.cpp"
					"Config/ArcDriveConfig.hpp"
					"Config/ConfigData.hpp" "Config/ConfigData.cpp"
					"Config/Datatypes.hpp"
					# Manager Config:
					"MngConfig.hpp"
					"MngConfigVersion.hpp"
				)
endif()

###########################################################
# WARNING: About the linking libraries:
# --------------------------------------------------------
# For some reason, the methods in the libraries are not
# recognized directly, resulting in LINK2019 with MSVC or
# "undefined reference to" in GCC, but the methods are generated
# and exported. To mitigate this problem, set as "True" the
# CMake variable "UseManualTargetLinkLibs" to link then manually.
###########################################################

set(UseManualTargetLinkLibs False)

if(UseManualTargetLinkLibs)
	if (WIN32)
		if(DebugMngConfigLib)
			#target_link_libraries(MngConfig ${ReposRoot}/build/MngConfig/Libs/<lib>/Debug/<libfile>.lib)
		else()
			#target_link_libraries(MngConfig ${ReposRoot}/build/MngConfig/Libs/<lib>/Release/<libfile>.lib)
		endif()
	else()
		#target_link_libraries(MngConfig ${ReposRoot}/build/bin/lib<libName>.so)
	endif()
else()
	#target_link_libraries(MngConfig <librojectName>)
	target_link_libraries(MngConfig VersionLib)
endif()