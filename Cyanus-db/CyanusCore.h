// CyanusCore.h
#ifndef _CYANUS_CORE_H_
#define _CYANUS_CORE_H_
#include "CyanusDB.h"
class CyanusCore {
private:
    CyanusDB db;
    CyanusCore() {}
    CyanusCore(const CyanusCore&) = delete;
    CyanusCore& operator=(const CyanusCore&) = delete;
public:
    static CyanusCore& getInstance() {
        static CyanusCore instance;
        return instance;
    }

    CyanusDB& getDB() {
        return db;
    }
};

#endif
