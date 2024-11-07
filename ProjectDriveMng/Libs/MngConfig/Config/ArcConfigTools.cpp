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

int ArcLib::Config::Tools::setDirectories(std::vector<ArcLib::Config::Datatypes::ProjectDriveMngFolder>* folders)
{
	int fail2Create = 0;
	std::vector<ArcLib::Config::Datatypes::ProjectDriveMngFolder> foldersStatus;

	for (int i = 0; i <= ArcLib::Config::Datatypes::ProjectDriveFolders::ProjectDriveMngCache; i++)
	{
		switch (i)
		{
			case ArcLib::Config::Datatypes::ProjectDriveFolders::UserHome:
			case ArcLib::Config::Datatypes::ProjectDriveFolders::ProjectDriveMngProgram:
			{
				break;
			}
			default:
			{
				std::filesystem::path path = resolveDirectory(static_cast<ArcLib::Config::Datatypes::ProjectDriveFolders>(i));
				
				ArcLib::Config::Datatypes::ProjectDriveMngFolder folder;

				folder.folder = static_cast<ArcLib::Config::Datatypes::ProjectDriveFolders>(i);
				folder.path = path;

				if (folder.path.empty())
				{
					fail2Create++;
					break;
				}

				if (!std::filesystem::exists(folder.path))
				{
					try
					{
						std::error_code err;
						if (std::filesystem::create_directories(folder.path, err))
						{
							folder.err = err;
						}
						else
						{
							folder.err = err;
							fail2Create++;
						}
					}
					catch(const std::exception& e)
					{
						fail2Create++;
					}
				}

				foldersStatus.push_back(folder);
				break;
			}
		}
	}

	if (folders != nullptr)
	{
		*folders = foldersStatus;
	}

    return fail2Create;
}

std::filesystem::path ArcLib::Config::Tools::resolveDirectory(ArcLib::Config::Datatypes::ProjectDriveFolders folder)
{
	std::filesystem::path path;
	std::filesystem::path folderPartialPath;

	#ifdef WIN32
	KNOWNFOLDERID folderId;
	#else
	std::string folderId;
	#endif // !WIN32

	// Get the KNOWNFOLDERID or folder name for environment:
	switch (folder)
	{
		case ArcLib::Config::Datatypes::ProjectDriveFolders::UserHome:
		{
			#ifdef WIN32
				folderId = KNOWNFOLDERID::FOLDERID_LocalAppData;
			#else
				folderId = "HOME";
			#endif // !WIN32
			break;
		}
		case ArcLib::Config::Datatypes::ProjectDriveFolders::ProjectDriveMngProgram:
		{
			#ifdef WIN32
				folderId = KNOWNFOLDERID::FOLDERID_UserProgramFiles;
			#else
				folderId = "HOME";
			#endif // !WIN32
			break;
		}
		case ArcLib::Config::Datatypes::ProjectDriveFolders::ProjectDriveMngConfig:
		case ArcLib::Config::Datatypes::ProjectDriveFolders::ProjectDriveMngCache:
		{
			#ifdef WIN32
				folderId = KNOWNFOLDERID::FOLDERID_LocalAppData;
			#else
				folderId = "HOME";
			#endif // !WIN32
			break;
		}
		default:
		{
			break;
		}
	}

	// Get the folder base path:
	#ifdef WIN32
	PWSTR* wPath;
	HRESULT hr = SHGetKnownFolderPath(folderId, 0, NULL, wPath);

	if (hr)
	{
		std::wstring wsPath = *wPath;
		path = wsPath;
	}

	CoTaskMemFree(wPath);
	#else
	path = std::getenv(folderId.c_str());
	#endif // !WIN32

	// Add the complementary folder path:
	switch (folder)
	{
		case ArcLib::Config::Datatypes::ProjectDriveFolders::ProjectDriveMngProgram:
		{
			#ifdef WIN32
				folderPartialPath = "ProjectDriveMng";
			#else
				folderPartialPath = ".local/bin/ProjectDriveMng";
			#endif // !WIN32
			break;
		}
		case ArcLib::Config::Datatypes::ProjectDriveFolders::ProjectDriveMngConfig:
		{
			#ifdef WIN32
				folderPartialPath = "ProjectDriveMng\\Config";
			#else
				folderPartialPath = ".config/ProjectDriveMng";
			#endif // !WIN32
			break;
		}
		case ArcLib::Config::Datatypes::ProjectDriveFolders::ProjectDriveMngCache:
		{
			#ifdef WIN32
				folderPartialPath = "ProjectDriveMng\\Cache";
			#else
				folderPartialPath = ".cache/ProjectDriveMng";
			#endif // !WIN32
			break;
		}
		default:
		{
			break;
		}
	}

	// Add the folder information into the folder struct:
	std::filesystem::path finalPath = path / folderPartialPath;
    
	return finalPath;
}

std::vector<std::filesystem::path> ArcLib::Config::Tools::getSettingFiles(std::filesystem::path configRoot, std::string ext)
{
    std::vector<std::filesystem::path> files;

	if (!std::filesystem::exists(configRoot))
	{
		return files;
	}

	bool anyExt = false;

	if (ext.empty() || ext == "*")
	{
		anyExt = true;
	}
	else
	{
		// Prepare the extension filter:

		if (ext.starts_with('*'))
		{
			ext.erase(0, 1);
		}

		if (!ext.starts_with('.'))
		{
			ext = "." + ext;
		}
	}

	for (const std::filesystem::directory_entry& d : std::filesystem::directory_iterator(configRoot))
	{
		if (d.is_regular_file())
		{
			if (anyExt)
			{
				files.push_back(d.path());
			}
			else
			{
				if (d.path().has_extension())
				{
					if (d.path().extension().string() == ext)
					{
						files.push_back(d.path());
					}
				}
			}
		}
	}

	return files;
}
