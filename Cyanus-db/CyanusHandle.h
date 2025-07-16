#ifndef _CYANUS_HANDLE_H_
#define _CYANUS_HANDLE_H_

#include "CyanusDB.h"
#include <winsock2.h> 

class CyanusHandle {
private:
	CyanusDB& db;
	int port;

	SOCKET serverSocket; 
	bool running;         
public:
	CyanusHandle(CyanusDB& database);
	~CyanusHandle();
	bool start(const int port);
	bool start();
	bool stop();

	void handleClient(SOCKET clientSocket);

	CyanusDB& getDB();
};

#endif
