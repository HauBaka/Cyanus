#define _HAS_STD_BYTE 0
#include "CyanusCore.h"
#include "CyanusDB.h"
#include "CyanusHandle.h"
#include <csignal>


void handleCtrlC(int signal) {
	std::cout << "\n[INFO] Saving database before exit...\n";
	CyanusCore::getInstance().getDB().save();
	exit(0); 
}


int main() {
	CyanusCore::getInstance().getDB().load();
	signal(SIGINT, handleCtrlC);
	CyanusHandle handle(6969);
	handle.start(); 

	CyanusCore::getInstance().getDB().save();
}