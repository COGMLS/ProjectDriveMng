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

#ifdef WIN32
	#define HOME_BASE_DIRECTORY "USERPROFILE"
#else
	#define HOME_BASE_DIRECTORY "HOME"
#endif // WIN32

namespace ArcLib
{
	namespace Config
	{
		namespace Datatypes
		{
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

			enum DefaultSettings : unsigned short
			{
				DEFAULT_SETTING_GENERAL_CONFIG,
				DEFAULT_SETTING_DRIVE_CONFIG,
				DEFAULT_SETTING_PROJECT_CONFIG,
				DEFAULT_SETTING_GIT_CONFIG
			};
		}
	}
}

#endif // !ARC_CONFIG_DATATYPES_HPP