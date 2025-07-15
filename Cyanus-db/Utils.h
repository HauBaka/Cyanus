#ifndef _UTILS_
#define _UTILS_
#include <string>
#include <fstream>
#define ll long long
using namespace std;
class Utils {
public:
	static ll getCurrentTime();
	static const string& hashPassword(const string& password);
	static void writeString(ofstream& ofs, const string& s);
	static void readString(ifstream& ifs, string& s);
};
#endif