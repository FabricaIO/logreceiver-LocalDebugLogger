#include "LocalDebugLogger.h"

/// @brief Creates a local debug logger
/// @param LogPath The path to the log file
LocalDebugLogger::LocalDebugLogger(String LogPath) {
	log_path = LogPath;
	Description.name = "Local Debug Logger";
	Description.version = "0.8";
}

bool LocalDebugLogger::receiveMessage(char message) {
	if (message != '\n' && message != '\r') {
		return writeLog(String(message));
	} else {
		return true;
	}
}

bool LocalDebugLogger::receiveMessage(String message) {
	if (message != "\r\n") {
		return writeLog(message);
	} else {
		return true;
	}
}

/// @brief Writes a message to the log file
/// @param message The message to write
/// @return True on success
bool LocalDebugLogger::writeLog(String message) {
	String data = TimeInterface::getFormattedTime("%m-%d-%Y %T") + ": " + message + "\n";
	if (Storage::getMediaType() == Storage::Media::Not_Ready) {
		startup_cache.push_back(data);
		return true;
	} else {
		if (!cache_flushed) {
			file_system = Storage::getFileSystem();
			if (!file_system->exists(log_path)) {
				File f = file_system->open(log_path, FILE_WRITE);
				f.print("");
				f.close();
			}
			File f = file_system->open(log_path, FILE_APPEND);
			for (const auto& line : startup_cache) {
				f.print(line);
			}
			startup_cache.clear();
			startup_cache.shrink_to_fit();
			cache_flushed = true;
			f.close();
		}
		File f = file_system->open(log_path, FILE_APPEND);
		bool success = f.print(data) > 0;
		f.close();
		return success;
	}
}