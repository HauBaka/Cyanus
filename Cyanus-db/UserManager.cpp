#include "UserManager.h"

string UserManager::hashPassword(const string& password) {

}

bool UserManager::checkPassword(const User& user, const string& password) {
	return user.getHashedPassword() == hashPassword(password);
}
