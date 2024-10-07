#pragma once

#ifndef VERSION_DATABASE_HPP
#define VERSION_DATABASE_HPP

#include <array>
#include <string>

#include "ProjectDriveMngVersion.hpp"
#include "../Libs/Imported/VersionLib/VersionLib.hpp"

const std::array<std::string, 3> verMinDb = 
{
	"0.1.0",	// Console Extensions
	"3.0.0", 	// LoggerLib
	"0.8.0"	 	// VersionLib
};

#endif // !VERSION_DATABASE_HPP