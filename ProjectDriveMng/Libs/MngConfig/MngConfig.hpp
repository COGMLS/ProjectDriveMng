#pragma once

#ifndef MANAGER_CONFIG_HPP
#define MANAGER_CONFIG_HPP

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

#include "Config/ArcDriveConfig.hpp"
#include "MngConfigVersion.hpp"

#include "VersionLib.hpp"

namespace ArcLib
{
	namespace Config
	{
		ARC_LIB_API inline VersionLib::VersionData getLibVersion()
		{
			VersionLib::VersionData ver(
				MANAGER_CONFIG_MAJOR_VERSION,
				MANAGER_CONFIG_MINOR_VERSION,
				MANAGER_CONFIG_PATCH_VERSION,
				MANAGER_CONFIG_BUILD_NUMBER,
				MANAGER_CONFIG_BUILD_TYPE,
				MANAGER_CONFIG_REVISION_NUMBER
			);
			return ver;
		}
	}
}

#endif // !MANAGER_CONFIG_HPP