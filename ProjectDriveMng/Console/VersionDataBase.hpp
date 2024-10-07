#pragma once

#ifndef VERSION_DATABASE_HPP
#define VERSION_DATABASE_HPP

#include <array>
#include <string>

#include "ProjectDriveMngVersion.hpp"
#include "../Libs/Imported/VersionLib/VersionLib.hpp"

#include "LoggerLibVersionTools.hpp"
#include "ConsoleExtVersionTools.hpp"

const std::array<std::string, 3> verMinDb = 
{
	"0.1.0",	// Console Extensions
	"3.0.0", 	// LoggerLib
	"0.8.0"	 	// VersionLib
};

VersionLib::VersionData ProjectDriveMng_vInfo(
	PROJECT_DRIVE_MANAGER_MAJOR_VERSION,
	PROJECT_DRIVE_MANAGER_MINOR_VERSION,
	PROJECT_DRIVE_MANAGER_PATCH_VERSION,
	PROJECT_DRIVE_MANAGER_BUILD_NUMBER,
	VersionLib::BuildType::ALPHA,//VersionLib::str2BuildType(PROJECT_DRIVE_MANAGER_BUILD_TYPE),
	PROJECT_DRIVE_MANAGER_REVISION_NUMBER
);

ConsoleExt::Version ConsoleExt_vStrcutInfo = ConsoleExt::getLibVersion();
LoggerLib::Version LoggerLib_vStructInfo = LoggerLib::getLibVersion();

VersionLib::VersionData ConsoleExt_vInfo(ConsoleExt::getVersionStr(ConsoleExt_vStrcutInfo, true, true));
VersionLib::VersionData LoggerLib_vInfo(LoggerLib::getVersionStr(LoggerLib_vStructInfo, true, true));
VersionLib::VersionData VersionLib_vInfo(VersionLib::internalVersionData);

#endif // !VERSION_DATABASE_HPP