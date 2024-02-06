#pragma once

#ifndef DRIVE_LIBRARY_DEFINE_HPP
#define DRIVE_LIBRARY_DEFINE_HPP

	#ifdef DRIVELIB_EXPORTS
		#define DRIVE_LIB_API __declspec(dllexport)
	#else
		#define DRIVE_LIB_API __declspec(dllimport)
	#endif //!DRIVELIB_EXPORT

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)

#endif //!DRIVE_LIBRARY_DEFINE_HPP