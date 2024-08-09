#include <iostream>
#include <filesystem>
#include <stdexcept>

#include <unistd.h>

#include "definitions.hpp"
#include "places.hpp"
#include "config.hpp"
#include "directory.hpp"

int main (int argc, const char* argv[], const char* argp[])
{
	//size_t argpSize = 0;
	//while (argp[++argpSize] != NULL);
	//std::cout << "argp size: " << argpSize << std::endl;

	__uid_t me = getuid();
	__uid_t myprivs = geteuid();

	if (me != myprivs)
	{
		std::cout << "User ID: " << me << " | User privileges: " << myprivs <<std::endl;
		std::cout << "This program is designed to run only with current user privileges!" << std::endl << "Aborting the application." << std::endl;
		return -1;
	}

	if (me == 0)
	{
		std::cout << "User ID: " << me << " | User privileges: " << myprivs <<std::endl;
		std::cout << "This program is designed to run only with non root privileges!" << std::endl << "Aborting the application." << std::endl;
		return -2;
	}

	std::cout << "Check for Remote Link Selector dir: " << chkRemoteLinkSelectorDir() << std::endl;

	configData cfg;
	cfg.version = 1;
	cfg.computer = "MY-PC-1";
	cfg.description = "Connect to main development git server";
	cfg.source = "/home/user/Places/RemotePcProjectDrive";

	std::cout << "Save file: " << saveFile(cfg) << std::endl;

	std::vector<std::filesystem::path> cfgFiles = getConfigFiles();

	for (size_t i = 0; i < cfgFiles.size(); i++)
	{
		std::cout << cfgFiles[i].stem() << std::endl;
	}

	configData cfg2 = loadFile(cfgFiles[0]);

	if (cfg2.version > 0)
	{
		std::cout << "Set remote ref path: " << cfg2.source << std::endl;
		std::cout << "Set remote ref: " << setRemoteRefSymLink(cfg2.source) << std::endl;
	}
	else
	{
		std::cout << "This configuration is not defined! Error: " << cfg2.version << std::endl;
	}

	return 0;
}