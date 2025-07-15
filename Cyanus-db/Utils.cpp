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
