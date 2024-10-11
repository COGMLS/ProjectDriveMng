#pragma once

#ifndef ARC_DRIVE_LIB_VERSION_TOOL_HPP
#define ARC_DRIVE_LIB_VERSION_TOOL_HPP

#ifdef WIN32
	#ifdef ARC_DRIVE_LIB_EXPORTS
		#define ARC_DRIVE_LIB_API __declspec(dllexport)
	#else
		#define ARC_DRIVE_LIB_API __declspec(dllimport)
	#endif //!ARC_DRIVE_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef ARC_DRIVE_LIB_EXPORTS
			#define ARC_DRIVE_LIB_API __attribute__((visibility("default")))
		#else
			#define ARC_DRIVE_LIB_API __attribute__((visibility("default")))
		#endif //!ARC_DRIVE_LIB_EXPORTS
	#else
		#ifdef ARC_DRIVE_LIB_EXPORTS
			#define ARC_DRIVE_LIB_API
		#else
			#define ARC_DRIVE_LIB_API
		#endif //!ARC_DRIVE_LIB_EXPORTS
	#endif
#endif // !WIN32

#include "ArcLibVersion.hpp"

#include <string>
#include <cstring>

namespace ArcLib
{
	/**
	 * @brief Archive Library Version number
	 */
	struct Version
	{
		unsigned int major;
		unsigned int minor;
		unsigned int patch;
		unsigned long long build;
		unsigned int revision;
		char* type;
	};

	/**
	 * @brief Get the Archive Library version
	 * @return Return a Version struct
	 */
	ARC_DRIVE_LIB_API inline ArcLib::Version getLibVersion()
	{
		ArcLib::Version v;
		v.major = ARC_DRIVE_LIB_MAJOR_VERSION;
		v.minor = ARC_DRIVE_LIB_MINOR_VERSION;
		v.patch = ARC_DRIVE_LIB_PATCH_VERSION;
		v.build = ARC_DRIVE_LIB_BUILD_NUMBER;
		v.revision = ARC_DRIVE_LIB_REVISION_NUMBER;
		v.type = static_cast<char*>(ARC_DRIVE_LIB_BUILD_TYPE);
		return v;
	}

	/**
	 * @brief Transform the struct Version into a string version
	 * @param version Archive Library Version struct
	 * @param showBuild Show the build number.
	 * @param showType Show the build type.
	 * @return Return a string version.
	 */
	ARC_DRIVE_LIB_API inline std::string getVersionStr (ArcLib::Version version, bool showBuild, bool showType)
	{
		std::string s;
		s = std::to_string(version.major) + "." + std::to_string(version.minor) + "." + std::to_string(version.patch);

		if (showType && !(std::strcmp(version.type, "release") == 0 || std::strcmp(version.type, "RELEASE") == 0))
		{
			s += "-" + std::string(version.type);
		}

		if (version.revision > 0)
		{
			s += "." + std::to_string(version.revision);
		}

		if (showBuild)
		{
			s += " build " + std::to_string(version.build);
		}

		return s;
	}
}

#endif // !ARC_DRIVE_LIB_VERSION_TOOL_HPP