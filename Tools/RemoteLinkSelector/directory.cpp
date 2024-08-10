#include "directory.hpp"

std::filesystem::path getHomePath()
{
	std::string home = std::getenv("HOME");

	if (home.empty())
	{
    	return std::filesystem::path();
	}

	return std::filesystem::path(home);
}

std::filesystem::path getPlacesPath()
{
	std::filesystem::path home = getHomePath();

	if (home.empty())
	{
		return std::filesystem::path();
	}

	std::filesystem::path places = home / PLACES_DIR;

	return places;
}

bool placesDirExists()
{
	std::filesystem::path home = getHomePath();

	if (home.empty())
	{
		return false;
	}

	std::filesystem::path places = home / PLACES_DIR;

	return std::filesystem::exists(places);
}

std::filesystem::path getRemoteLinkSelectorPath()
{
	std::filesystem::path home = getHomePath();

	if (home.empty())
	{
		return std::filesystem::path();
	}

	std::filesystem::path remoteLinkSel = home / REMOTE_GIT_CONFIG_DIR;

	return remoteLinkSel;
}

bool remoteLinkSelectorDirExists()
{
    std::filesystem::path remoteLnkSel = getHomePath();

	if (remoteLnkSel.empty())
	{
		return false;
	}

	remoteLnkSel = remoteLnkSel / REMOTE_GIT_CONFIG_DIR;

	return std::filesystem::exists(remoteLnkSel);
}

int chkRemoteLinkSelectorDir()
{
    try
	{
		std::filesystem::path home = getHomePath();

		if (home.empty())
		{
			return -2;
		}

		std::filesystem::path remoteLinkSel = getRemoteLinkSelectorPath();

		if (!std::filesystem::exists(remoteLinkSel) && !remoteLinkSel.empty())
		{
			if (std::filesystem::create_directories(remoteLinkSel))
			{
				return 1;
			}

			return -3;
		}

		if (!remoteLinkSel.empty())
		{
			if (std::filesystem::is_directory(remoteLinkSel))
			{
				return 0;
			}
		}

		return -4;
	}
	catch(const std::exception&)
	{
		return -1;
	}
}
