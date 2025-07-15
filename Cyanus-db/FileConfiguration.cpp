#include "FileConfiguration.h"

FileConfiguration::FileConfiguration(const Mode& mode, const string& filename) {
	this->mode = mode;
	this->filename = filename;
	if (mode == READ) {
		ifs.open(this->filename);
	}
	else ofs.open(this->filename);
}