#pragma once

#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <filesystem>
#include <string>
#include <cstdlib>

#include "definitions.hpp"

/// @brief Get the Home path
std::filesystem::path getHomePath();

/// @brief Get the path to Places directory
std::filesystem::path getPlacesPath();

/// @brief Verify if the Places directory exists
bool placesDirExists();

/// @brief Get the path to RemoteLinkSelector configuration folder
std::filesystem::path getRemoteLinkSelectorPath();

/// @brief Verify if the RemoteLinkSelector exists
bool remoteLinkSelectorDirExists();

/**
 * @brief Verify if the path to RemoteLinkSelector exist and create the directories if need.
 * @return 1 means the directory was created. 0 means the directory already exist. Negative values represent an fail.
 */
int chkRemoteLinkSelectorDir();

#endif // !DIRECTORY_HPP