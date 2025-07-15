#ifndef _UTILS_
#define _UTILS_
#include <string>
#define ll long long
using namespace std;
class Utils {
public:
	static ll getCurrentTime();
	static const string& hashPassword(const string& password);
};
#endif