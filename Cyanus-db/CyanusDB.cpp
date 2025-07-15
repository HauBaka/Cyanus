#include "AVLTree.h"
#include "UserManager.h"
class CyanusDB {
private:
	UserManager userMng;
public:
	UserManager& userManager();

	void save();
	void load();
};