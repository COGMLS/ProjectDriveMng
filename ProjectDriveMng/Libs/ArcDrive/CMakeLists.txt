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

# Define local Settings Library project root var:
set(ArcMngRoot ${CMAKE_CURRENT_LIST_DIR})

# Define if is Windows Environment:

if(WIN32)
	add_compile_definitions(WIN32)
	add_compile_definitions(_WINDOWS)
	add_compile_definitions(_USRDLL)
	add_compile_definitions(_WINDLL)
endif()

if (DebugSolution AND NOT DebugArcMngLib)
	set(DebugArcMngLib True)
endif()

if(DebugArcMngLib)
	add_compile_definitions(DEBUG)
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Define the project:
project(
			ArcMng
			VERSION 0.0.1
			DESCRIPTION "Archive Library for Project Drive Manager"
		)

###########################################################
#
# Project components settings:
#
###########################################################

# Include libraries directories source codes:
#include_directories("${ReposRoot}/Libraries/<lib>")
include_directories("${ArcMngRoot}")
include_directories("${ArcMngRoot}/Config")
include_directories("${ArcMngRoot}/Drive")
include_directories("${ArcMngRoot}/Project")

# Define to export the library methods if is Windows:
if(WIN32)
	# Add the export here
	add_compile_definitions(ARC_DRIVE_LIB_EXPORTS)
	add_compile_definitions(ARC_PROJECT_LIB_EXPORTS)
	add_compile_definitions(ARC_MANAGER_LIB_EXPORTS)
	add_compile_definitions(ARC_CONFIG_LIB_EXPORTS)
endif()

if (WIN32)
	add_library(
					ArcMng
					SHARED
					"dllmain.hpp" "dllmain.cpp"
					# Config library part:
					"Config/ArcConfig.hpp"
					"Config/ArcConfigTools.hpp"
					# Drive Library part:
					"Drive/ArcDrive.hpp" "Drive/ArcDrive.cpp"
					# Project Library part:
					# General Archive Manager part:
					"ArcLibVersion.hpp"
					"ArcLibVersionTools.hpp"
					"ArcMng.hpp"
				)
else()
	add_library(
					ArcMng
					SHARED
					# Config library part:
					"Config/ArcConfig.hpp"
					"Config/ArcConfigTools.hpp"
					# Drive Library part:
					"Drive/ArcDrive.hpp" "Drive/ArcDrive.cpp"
					# Project Library part:
					# General Archive Manager part:
					"ArcLibVersion.hpp"
					"ArcLibVersionTools.hpp"
					"ArcMng.hpp"
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
		if(DebugArcMngLib)
			#target_link_libraries(ArcMng ${ReposRoot}/build/ArcMng/Libs/<lib>/Debug/<libfile>.lib)
		else()
			#target_link_libraries(ArcMng ${ReposRoot}/build/ArcMng/Libs/<lib>/Release/<libfile>.lib)
		endif()
	else()
		#target_link_libraries(ArcMng ${ReposRoot}/build/bin/lib<libName>.so)
	endif()
else()
	#target_link_libraries(ArcMng <librojectName>)
endif()