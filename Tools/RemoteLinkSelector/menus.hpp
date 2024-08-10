#pragma once

#ifndef MENUS_HPP
#define MENUS_HPP

#include <string>
#include <filesystem>
#include <vector>

#include "definitions.hpp"
#include "directory.hpp"
#include "config.hpp"
#include "places.hpp"

std::vector<std::string> getDirectoriesStatus();
std::vector<std::string> getHelp();
std::vector<std::string> getConfigInfo(configData& cfgData);
std::vector<std::string> showConfigsList(std::vector<std::filesystem::path>& cfgFilesList);

#endif // !MENUS_HPP