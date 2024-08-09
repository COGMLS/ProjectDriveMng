#pragma once

#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#ifndef __linux__
	#error This tool is only for Linux OS!
#endif // __linux__

#define PLACES_DIR "Places"
#define REMOTE_GIT_SERVER_SYMLINK "RemoteGitServer"
#define REMOTE_GIT_CONFIG_DIR ".config/ProjectDriveMng/RemoteLinkSelector"
#define REMOTE_CONFIG_EXT ".ini"

#endif // !DEFINITIONS_HPP