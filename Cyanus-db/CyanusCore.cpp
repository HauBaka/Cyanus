#define _HAS_STD_BYTE 0
#include "CyanusDB.h"
#include "CyanusHandle.h"
#include <csignal>

CyanusDB* globalDB = nullptr;

void handleCtrlC(int signal) {
	if (globalDB) {
		std::cout << "\n[INFO] Saving database before exit...\n";
		globalDB->save();
	}
	exit(0); 
}


int main() {
	CyanusDB db;
	db.load();
	globalDB = &db;
	signal(SIGINT, handleCtrlC);
	CyanusHandle handle(db);
	handle.start(6969); // Start server on port 6969

	db.save();
}