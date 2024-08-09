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
