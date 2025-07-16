#define _HAS_STD_BYTE 0
#include "CyanusDB.h"
#include "CyanusHandle.h"
int main() {
	CyanusDB db;
	db.load();
	
	CyanusHandle handle(db);
	handle.start(6969); // Start server on port 6969

	db.save();
}