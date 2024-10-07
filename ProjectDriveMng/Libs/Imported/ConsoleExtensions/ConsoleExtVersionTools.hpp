#pragma once

#ifndef CONSOLE_EXT_VERSION_TOOLS_HPP
#define CONSOLE_EXT_VERSION_TOOLS_HPP

#ifdef WIN32
	#ifdef CONSOLE_EXT_VERSION_EXPORTS
		#define CONSOLE_EXT_VERSION_LIB_API __declspec(dllexport)
	#else
		#define CONSOLE_EXT_VERSION_LIB_API __declspec(dllimport)
	#endif //!CONSOLE_EXT_VERSION_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef CONSOLE_EXT_VERSION_EXPORTS
			#define CONSOLE_EXT_VERSION_LIB_API __attribute__((visibility("default")))
		#else
			#define CONSOLE_EXT_VERSION_LIB_API __attribute__((visibility("default")))
		#endif //!CONSOLE_EXT_VERSION_EXPORTS
	#else
		#ifdef CONSOLE_EXT_VERSION_EXPORTS
			#define CONSOLE_EXT_VERSION_LIB_API
		#else
			#define CONSOLE_EXT_VERSION_LIB_API
		#endif //!CONSOLE_EXT_VERSION_EXPORTS
	#endif
#endif // !WIN32

#include "ConsoleExtVersion.hpp"
#include <string>

/**
 * @brief Console Extensions
 */
namespace ConsoleExt
{
	/**
	 * @brief Console Extensions Version number
	 */
	struct Version
	{
		unsigned int major;
		unsigned int minor;
		unsigned int revision;
		unsigned int build;
		char* type;
	};

	/**
	 * @brief Get the Console Extensions Library version
	 * @return Return a Version struct
	 */
	CONSOLE_EXT_VERSION_LIB_API inline ConsoleExt::Version getLibVersion()
	{
		Version v;
		v.major = CONSOLE_EXT_MAJOR_VERSION;
		v.minor = CONSOLE_EXT_MINOR_VERSION;
		v.revision = CONSOLE_EXT_REVISION_NUMBER;
		v.build = CONSOLE_EXT_BUILD_NUMBER;
		v.type = CONSOLE_EXT_BUILD_TYPE;
		return v;
	}

	/**
	 * @brief Transform the struct Version into a string version
	 * @param version Console Extensions Version struct
	 * @param showBuild Show the build number.
	 * @param showType Show the build type.
	 * @return Return a string version.
	 */
	CONSOLE_EXT_VERSION_LIB_API inline std::string getVersionStr (ConsoleExt::Version& version, bool showBuild, bool showType)
	{
		std::string s;
		s = std::to_string(version.major) + "." + std::to_string(version.minor) + "." + std::to_string(version.revision);

		if (showType)
		{
			s += "-" + std::string(version.type);
		}

		if (showBuild)
		{
			s += " build " + std::to_string(version.build);
		}

		return s;
	}
}

#endif // !CONSOLE_EXT_VERSION_TOOLS_HPP