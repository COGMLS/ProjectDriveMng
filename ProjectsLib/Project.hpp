#pragma once

#ifndef PROJECT_LIBRARY_HPP
#define PROJECT_LIBRARY_HPP

#include "pch.h"

class Project
{
	private:
		// Basic project informations:
		std::filesystem::path path;
		std::wstring name;
		bool exists;
		bool isGitRepos;


	public:

};

#endif // !PROJECT_LIBRARY_HPP