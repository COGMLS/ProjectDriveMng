#pragma once

#ifndef ARC_DRIVE_LIB_HPP
#define ARC_DRIVE_LIB_HPP

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

#include <vector>
#include <string>
#include <filesystem>
#include <thread>
#include <memory>

namespace ArcLib
{
	namespace Drive
	{
		std::vector<std::filesystem::path> getRootPaths();
	}
}

#endif // !ARC_DRIVE_LIB_HPP