#pragma once

#ifndef ARC_CONFIG_TOOLS_HPP
#define ARC_CONFIG_TOOLS_HPP

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

#include "Datatypes.hpp"

#ifdef WIN32
#include <shlobj_core.h>
#include <combaseapi.h>
#else
#include <cstdlib>
#endif // !WIN32

/**************************************
 * Directories to create:
 * ----------------------------------
 * On Linux:
 * $HOME/.config/ProjectDriveMng
 * $HOME/.cache/ProjectDriveMng
 * --------------------------
 * On Windows:
 * %USERPROFILE%\AppData\Local\ProjectDriveMng
 * %USERPROFILE%\AppData\Local\ProjectDriveMng\Config
 * %USERPROFILE%\AppData\Local\ProjectDriveMng\Cache
**************************************/

namespace ArcLib
{
	namespace Config
	{
		namespace Tools
		{
			std::vector<std::string> getDefaultSettings();

			int setDirectories(std::vector<ArcLib::Config::Datatypes::ProjectDriveMngFolder>* folders = nullptr);

			std::filesystem::path resolveDirectory(ArcLib::Config::Datatypes::ProjectDriveFolders folder);

			std::vector<std::filesystem::path> getSettingFiles(std::filesystem::path configRoot);
		}
	}
}

#endif // !ARC_CONFIG_TOOLS_HPP