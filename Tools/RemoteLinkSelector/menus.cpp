#include "menus.hpp"

std::vector<std::string> getDirectoriesStatus()
{
	std::vector<std::string> output;

	output.push_back("\tPlaces Exists: " + std::to_string(placesDirExists()));
	output.push_back("\tRemote Link Selector Exists: " + std::to_string(remoteLinkSelectorDirExists()));

	return output;
}

std::vector<std::string> getHelp()
{
    return std::vector<std::string>();
}

std::vector<std::string> getConfigInfo(configData& cfgData)
{
    std::vector<std::string> output;

	output.push_back("\tVersion: " + std::to_string(cfgData.version));
	output.push_back("\tDescription: " + cfgData.description);
	output.push_back("\tComputer: " + cfgData.computer);
	output.push_back("\tSource: " + cfgData.source);

	return output;
}

std::vector<std::string> showConfigsList(std::vector<std::filesystem::path> &cfgFilesList)
{
    std::vector<std::string> output;

	for (std::filesystem::path& p : cfgFilesList)
	{
		output.push_back(p.filename().stem());
	}

	return output;
}
