#pragma once

#ifndef PROJECTS_LIBRARY_DEFINE_HPP
#define PROJECTS_LIBRARY_DEFINE_HPP

	#ifdef PROJECTSLIB_EXPORTS
		#define PROJECTS_LIB_API __declspec(dllexport)
	#else
		#define PROJECTS_LIB_API __declspec(dllimport)
	#endif //!PROJECTSLIB_EXPORT

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)

#endif //!PROJECTS_LIBRARY_DEFINE_HPP