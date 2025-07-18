#include "Utils.h"
#include <chrono>
#include <iomanip>
#include <random>
#include <sstream>
#include <iostream>
using namespace std;

ll Utils::getCurrentTime() {
	auto now = chrono::system_clock::now();
	auto duration = now.time_since_epoch();

	ll milliseconds = chrono::duration_cast<chrono::milliseconds>(duration).count();
	return milliseconds;
}

/*
Example format: "%Y-%m-%d %H:%M:%S"
*/
string Utils::getCurrentTimeString(const string& format) {
	auto now = chrono::system_clock::now();
	time_t now_time = chrono::system_clock::to_time_t(now);
	tm local_tm;
	localtime_s(&local_tm, &now_time);
	stringstream ss;
	ss << put_time(&local_tm, format.c_str());
	return ss.str();
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

