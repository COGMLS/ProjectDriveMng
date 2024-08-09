#include "places.hpp"

std::vector<std::filesystem::path> getPlaces()
{
	std::filesystem::path places = getPlacesPath();
	
	if (places.empty())
	{
    	return std::vector<std::filesystem::path>();
	}

	std::vector<std::filesystem::path> symLink;

	for (std::filesystem::directory_entry d : std::filesystem::directory_iterator(places))
	{
		if (d.is_symlink())
		{
			symLink.push_back(d.path());
		}
	}

	return symLink;
}

std::filesystem::path getRemoteRefSymLink(std::vector<std::filesystem::path> &placesSymLinks)
{
	std::filesystem::path remoteGitRefLink;

	for (size_t i = 0; i < placesSymLinks.size(); i++)
	{
		if (placesSymLinks[i].filename().string() == REMOTE_GIT_SERVER_SYMLINK)
		{
			remoteGitRefLink = placesSymLinks[i];
			break;
		}
	}

	return remoteGitRefLink;
}

int setRemoteRefSymLink(std::filesystem::path newRef)
{
	std::vector<std::filesystem::path> links = getPlaces();

	std::filesystem::path remoteGitRefLink = getRemoteRefSymLink(links);

	if (remoteGitRefLink.empty())
	{
		if (getPlacesPath().empty())
		{
			return 1;
		}

		remoteGitRefLink = getPlacesPath() / REMOTE_GIT_SERVER_SYMLINK;
	}

	if (std::filesystem::exists(remoteGitRefLink))
	{
		if (std::filesystem::remove(remoteGitRefLink))
		{
			try
			{
				std::filesystem::create_symlink(newRef, remoteGitRefLink);
				return 0;
			}
			catch(const std::exception&)
			{
				return -1;
			}
		}
	}
	else
	{
		try
		{
			std::filesystem::create_symlink(newRef, remoteGitRefLink);
			return 0;
		}
		catch(const std::exception&)
		{
			return -1;
		}
	}

	return 2;
}
