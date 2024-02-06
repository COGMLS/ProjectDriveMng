#pragma once

#ifndef COMMON_LIBRARY_DEFINE_HPP
#define COMMON_LIBRARY_DEFINE_HPP

	#ifdef COMMONLIB_EXPORTS
		#define COMMON_LIB_API __declspec(dllexport)
	#else
		#define COMMON_LIB_API __declspec(dllimport)
	#endif //!COMMONLIB_EXPORT

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)

#endif //!COMMON_LIBRARY_DEFINE_HPP