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
	String data = TimeInterface::getFormattedTime("%m-%d-%Y %T") + ": " + message;
	if (Storage::getMediaType() == Storage::Media::Not_Ready) {
		startup_cache.push_back(data);
		return true;
	} else {
		if (!cache_flushed) {
			for (const auto& line : startup_cache) {
				if (!Storage::fileExists(log_path)) {
						Storage::writeFile(log_path, line);
				} else {
					Storage::appendToFile(log_path, line);
				}
			}
			startup_cache.clear();
			startup_cache.shrink_to_fit();
			cache_flushed = true;
		}
		if (!Storage::fileExists(log_path)) {
			return Storage::writeFile(log_path, data);
		} else {
			return Storage::appendToFile(log_path, data);
		}
	}
}