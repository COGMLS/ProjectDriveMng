#include <iostream>
#include <locale>
#include <filesystem>
#include <stdexcept>
#include <queue>

#include <unistd.h>

#include "definitions.hpp"
#include "places.hpp"
#include "config.hpp"
#include "directory.hpp"
#include "commands.hpp"
#include "menus.hpp"

int main (int argc, const char* argv[], const char* argp[])
{
	std::locale loc("en_US.UTF-8");
	std::locale::global(loc);

	//size_t argpSize = 0;
	//while (argp[++argpSize] != NULL);
	//std::cout << "argp size: " << argpSize << std::endl;

	// Check for user credentials:
	// NOTE: no root user is allowed by this application!

	uid_t me = getuid();
	uid_t myPrivileges = geteuid();

	if (me != myPrivileges)
	{
		std::cout << "User ID: " << me << " | User privileges: " << myPrivileges <<std::endl;
		std::cout << "This program is designed to run only with current user privileges!" << std::endl << "Aborting the application." << std::endl;
		return -1;
	}

	if (me == 0)
	{
		std::cout << "User ID: " << me << " | User privileges: " << myPrivileges <<std::endl;
		std::cout << "This program is designed to run only with non root privileges!" << std::endl << "Aborting the application." << std::endl;
		return -2;
	}

	// If the user credentials / privileges are correct, start the app:

	std::queue<cmd> cmdQueue;
	std::vector<std::string> cmdLineVec;

	for (size_t i = 1; i < argc; i++)
	{
		//cmdLineVec.push_back(argv[i]);
		cmdQueue.push(cmd(argv[i]));
	}

	// No arguments to work. Show the actual configuration:
	if (cmdQueue.size() == 0)
	{
		auto links = getPlaces();
		auto refLink = getRemoteRefSymLink(links);

		if (refLink.empty())
		{
			std::cout << "No git remote server reference link is set." << std::endl;
		}
		else
		{
			std::cout << "Current git remote server reference link path: " << refLink.string() << std::endl;
		}

		return 2;
	}

	while (!cmdQueue.empty())
	{
		cmd c = cmdQueue.front();

		if (c.getType() != ARGUMENT)
		{
			// Remove current command from queue
			cmdQueue.pop();

			switch (c.getType())
			{
				case CMDTYPE::HELP_CMD:
				{
					auto help = getHelp();

					for (std::string& l : help)
					{
						std::cout << l << std::endl;
					}

					return 0;
					//break;
				}
				case CMDTYPE::LIST_CMD:
				{
					if (cmdQueue.empty())
					{
						return 3;
					}

					if (cmdQueue.front().getType() == CMDTYPE::ARGUMENT)
					{
						cmd arg = cmdQueue.front();

						if (arg.getValue() == "config")
						{
							if (remoteLinkSelectorDirExists())
							{
								std::vector<std::filesystem::path> configFiles = getConfigFiles();
								std::vector<std::string> configList = showConfigsList(configFiles);

								for (std::string& l : configList)
								{
									std::cout << l << std::endl;
								}
							}
							else
							{
								std::cout << "Remote Link Selector doesn't exist!" << std::endl;
								std::cout << "Create a new configuration to define the directory." << std::endl;
							}
						}
						else if (arg.getValue() == "links")
						{
							if (placesDirExists())
							{
								std::vector<std::filesystem::path> placesLinks = getPlaces();

								for (std::filesystem::path& p : placesLinks)
								{
									std::cout << p.filename().stem() << " -> " << std::filesystem::read_symlink(p).string() << std::endl;
								}
							}
							else
							{
								std::cout << "Places directory doesn't exist!" << std::endl;
								std::cout << "Create the directory in home's root to be able to access it." << std::endl;
							}
						}
						else
						{
							return 4;
						}
					}
					else
					{
						return 4;
					}

					break;
				}
				case CMDTYPE::ADD_CMD:
				{
					std::string computer, description, source;

					std::cout << "Enter with the values for new configurations:" << std::endl;

					std::cout << "Computer: ";
					std::getline(std::cin, computer);
					std::cout << "Source: ";
					std::getline(std::cin, source);
					std::cout << "Description: ";
					std::getline(std::cin, description);

					if (computer.empty() || source.empty())
					{
						return 5;
					}

					configData newCfg;
					newCfg.computer = computer;
					newCfg.description = description;
					newCfg.source = source;
					newCfg.version = 1;

					int saveStatus = saveFile(newCfg);

					if (saveFile >= 0)
					{
						std::cout << "Configurations saved with success." << std::endl;
						return 0;
					}
					else
					{
						std::cout << "Fail to save your configurations. Exit Code: " << saveStatus << std::endl;
						return 5;
					}

					break;
				}
				case CMDTYPE::REMOVE_CMD:
				{
					
					break;
				}
				case CMDTYPE::SELECT_CMD:
				{
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}

	// ------------------------------------------------------------------- //

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