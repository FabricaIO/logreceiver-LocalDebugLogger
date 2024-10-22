#include "LocalDebugLogger.h"

/// @brief Creates a local debug logger
/// @param LogPath The path to the log file
LocalDebugLogger::LocalDebugLogger(String LogPath) {
	log_path = LogPath;
	Description.name = "Local Debug Logger";
	Description.version = "0.8";
}

bool LocalDebugLogger::receiveMessage(char message) {
	return writeLog(String(message));
}

bool LocalDebugLogger::receiveMessage(String message) {
	return writeLog(message);
}

/// @brief Writes a message to the log file
/// @param message The message to write
/// @return True on success
bool LocalDebugLogger::writeLog(String message) {
	String data = TimeInterface::getFormattedTime("%m-%d-%Y %T") + ": ";
	if (!Storage::fileExists(log_path)) {
		if (!Storage::writeFile(log_path, data + message)) {
			return false;
		} else {
			return true;
		}
	} else {
		return Storage::appendToFile(log_path, data + message);
	}
}