#pragma once

#ifndef VERSION_DATABASE_HPP
#define VERSION_DATABASE_HPP

#include <array>
#include <string>
#include <vector>

#include "ProjectDriveMngVersion.hpp"
#include "../Libs/Imported/VersionLib/VersionLib.hpp"

#include "LoggerLibVersionTools.hpp"
#include "ConsoleExtVersionTools.hpp"

const std::array<std::array<std::string, 2>, 3> verMinDb = 
{
	std::array<std::string, 2>{"Console Extensions", "0.1.0"},
	std::array<std::string, 2>{"LoggerLib", "3.0.0"},
	std::array<std::string, 2>{"VersionLib", "0.8.0"}
};

VersionLib::VersionData ProjectDriveMng_vInfo(
	PROJECT_DRIVE_MANAGER_MAJOR_VERSION,
	PROJECT_DRIVE_MANAGER_MINOR_VERSION,
	PROJECT_DRIVE_MANAGER_PATCH_VERSION,
	PROJECT_DRIVE_MANAGER_BUILD_NUMBER,
	VersionLib::str2BuildType(PROJECT_DRIVE_MANAGER_BUILD_TYPE),
	PROJECT_DRIVE_MANAGER_REVISION_NUMBER
);

const std::vector<VersionLib::VersionData> getVersionDb();

const std::vector<VersionLib::VersionData> getMinVersionDb();

// LibName MinVer ActualVer Status

const std::vector<std::array<std::string, 4>> testLibCompat (const std::vector<VersionLib::VersionData>& actualVer);

#endif // !VERSION_DATABASE_HPP