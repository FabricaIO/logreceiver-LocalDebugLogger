/*
* This file and associated .cpp file are licensed under the GPLv3 License Copyright (c) 2024 Sam Groveman
*
* Contributors: Sam Groveman
*/

#include <LogReceiver.h>
#include <Storage.h>

/// @brief Logs to the Arduino serial output
class LocalDebugLogger : public LogReceiver {
	public:
		LocalDebugLogger(String LogPath = "/debug.log");
		bool receiveMessage(char message);
		bool receiveMessage(String message);

	protected:		
		/// @brief Path to configuration file
		String log_path;
		bool writeLog(String message);
};