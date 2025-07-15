#include "Utils.h"
#include <chrono>
#include <iomanip>
#include <sstream>
using namespace std;

ll Utils::getCurrentTime() {
    auto now = chrono::system_clock::now();
    auto duration = now.time_since_epoch();

    ll milliseconds = chrono::duration_cast<chrono::milliseconds>(duration).count();
    return milliseconds;
}


void Utils::writeString(ofstream& ofs, const string& s) {
	int len = s.size();
	ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
	ofs.write(s.c_str(), len);
}

void Utils::readString(ifstream& ifs, string& s) {
	int len;
	ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
	s.resize(len); 
	ifs.read(&s[0], len);
}


const string& Utils::hashPassword(const string& password) {
	//Using polynomial hashing
	const int P = 32;
	const long long M = 1e9 + 97;
	long long hashValue = 0;

	for (int i = 0; i < password.size(); ++i)
		hashValue = (hashValue * P + password[i]) % M;

	stringstream ss;
	ss << hex << setw(16) << setfill('0') << hashValue;
	return ss.str();
}
