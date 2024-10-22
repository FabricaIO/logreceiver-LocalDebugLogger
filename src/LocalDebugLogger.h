/*
* This file and associated .cpp file are licensed under the GPLv3 License Copyright (c) 2024 Sam Groveman
*
* WARNING: This logger severely reduces the storage performance of the device to the point that large file operations may
*          crash the system and should only be used for debugging
*
* Contributors: Sam Groveman
*/

#include <LogReceiver.h>
#include <Storage.h>
#include <TimeInterface.h>
#include <vector>

/// @brief Logs to the local storage
class LocalDebugLogger : public LogReceiver {
	public:
		LocalDebugLogger(String LogPath = "/debug.log");
		bool receiveMessage(char message);
		bool receiveMessage(String message);

	protected:		
		/// @brief Path to log file
		String log_path;

		/// @brief Caches boot messages until storage is mounted
		std::vector<String> startup_cache;

		/// @brief Indicates the cached messages have been flushed
		bool cache_flushed = false;

		/// @brief File system in use
		FS* file_system;

		bool writeLog(String message);

};