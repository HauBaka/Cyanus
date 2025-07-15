#ifndef _FILECONFIGURATION_H_
#define _FILECONFIGURATION_H_
#include <string>
#include <fstream>
using namespace std;
class FileConfiguration {
public:
	enum Mode {
		READ, WRITE
	};

	FileConfiguration(const Mode&mode, const string& filename);

	auto getStream();

	void close();
private:
	Mode mode;
	string& filename;
	ofstream ofs;
	ifstream ifs;
};
#endif