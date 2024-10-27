#pragma once

#ifndef ARC_CONFIG_DATATYPES_HPP
#define ARC_CONFIG_DATATYPES_HPP

#ifdef WIN32
	#ifdef ARC_CONFIG_LIB_EXPORTS
		#define ARC_LIB_API __declspec(dllexport)
	#else
		#define ARC_LIB_API __declspec(dllimport)
	#endif //!ARC_CONFIG_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef ARC_CONFIG_LIB_EXPORTS
			#define ARC_LIB_API __attribute__((visibility("default")))
		#else
			#define ARC_LIB_API __attribute__((visibility("default")))
		#endif //!ARC_CONFIG_LIB_EXPORTS
	#else
		#ifdef ARC_CONFIG_LIB_EXPORTS
			#define ARC_LIB_API
		#else
			#define ARC_LIB_API
		#endif //!ARC_CONFIG_LIB_EXPORTS
	#endif
#endif // !WIN32

#include <filesystem>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <thread>
#include <array>
#include <map>
#include <system_error>

#ifdef WIN32
	#define HOME_BASE_DIRECTORY "USERPROFILE"
	#define PROJECT_DRIVE_MNG_CONFIG "LOCALAPPDATA"
	#define PROJECT_DRIVE_MNG_CACHE "LOCALAPP"
#else
	#define HOME_BASE_DIRECTORY "HOME"
	#define PROJECT_DRIVE_MNG_CONFIG ".config"
	#define PROJECT_DRIVE_MNG_CACHE ".cache"
#endif // WIN32

#define PROJECT_DRIVE_MNG_FOLDER "ProjectDriveMng"

namespace ArcLib
{
	namespace Config
	{
		namespace Datatypes
		{
			/**
			 * @brief Archive configuration datatype
			 */
			enum ArcConfigDataType : int
			{
				NOT_SET_CONFIG,
				NULL_CONFIG,
				STRING_CONFIG,
				INT_CONFIG,
				UINT_CONFIG,
				FLOAT_CONFIG,
				BOOLEAN_CONFIG,
				BINARY_CONFIG
			};

			/**
			 * @brief Archive Drive Libraries config tags
			 */
			enum DefaultSettings : int
			{
				DEFAULT_SETTING_GENERAL_CONFIG,
				DEFAULT_SETTING_DRIVE_CONFIG,
				DEFAULT_SETTING_PROJECT_CONFIG,
				DEFAULT_SETTING_GIT_CONFIG
			};

			/**
			 * @brief Enumerator for Project Drive Manager known folders
			 */
			enum ProjectDriveFolders : int
			{
				UserHome,					// %USERPROFILE% on Windows or $HOME on Linux
				ProjectDriveMngProgram,		// Return the program root path
				ProjectDriveMngConfig,		// %LOCALAPPDATA%\ProjectDriveMng\Config on Windows or $HOME\.config\ProjectDriveMng on Linux
				ProjectDriveMngCache		// %LOCALAPPDATA%\ProjectDriveMng\Cache on Windows or $HOME\.cache\ProjectDriveMng on Linux
			};

			/**
			 * @brief Project Drive Manager known folder struct
			 */
			struct ProjectDriveMngFolder
			{
				ProjectDriveFolders folder;
				std::filesystem::path path;
				std::error_code err;
			};
		}
	}
}

#endif // !ARC_CONFIG_DATATYPES_HPP