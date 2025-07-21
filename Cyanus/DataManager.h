#ifndef _DATAMANAGER_H
#define _DATAMANAGER_H

#include <string>
#include <iostream>
#include "UserManager.h"
using namespace std;

class DataManager {
private:
	DataManager() = default;
	DataManager(const DataManager&) = delete;
	DataManager& operator=(const DataManager&) = delete;

public:
	static DataManager& getInstance() {
		static DataManager instance;
		return instance;
	}
	void loadData();
	void saveData();
};

#endif // _DATAMANAGER_H