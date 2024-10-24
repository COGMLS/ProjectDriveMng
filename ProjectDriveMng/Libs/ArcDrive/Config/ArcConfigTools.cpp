#include "ArcConfigTools.hpp"

std::vector<std::string> ArcLib::Config::Tools::getDefaultSettings()
{
	std::vector<std::string> defaultFileConfig = 
	{
		"ProjectDriveRoot=",
		"ProjectDriveLabel=",
		"ProjectDriveLocalCache=",
		"ProjectDriveLocalGitRepos=",
		"ProjectDriveGitRepos=",
		"GitReposLabel=",
		"GitReposDefaultBranch=",
		"GitReposDefaultClone=",
		"GitReposBackupPath=",
		"GitReposArchivedPath=",
		"GitReposTempPath=",
	};

	return defaultFileConfig;
}

std::vector<std::filesystem::path> ArcLib::Config::Tools::getSettingFiles(std::filesystem::path configRoot)
{
    return std::vector<std::filesystem::path>();
}
