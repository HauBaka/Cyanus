#ifndef _CYANUS_H_
#define _CYANUS_H_
#include "SocketManager.h"
#include "UserManager.h"
class Cyanus {
private:
	SocketManager socketManager;
	Cyanus() {};
	Cyanus(const Cyanus&) = delete;
	Cyanus& operator=(const Cyanus&) = delete;
public:
	static Cyanus& getInstance() {
		static Cyanus instance;
		return instance;
	}
	void run();
	SocketManager& getSocketManager();
	UserManager& getUserManager();
};
#endif