#ifndef UMBRA_STORAGE_H
#define UMBRA_STORAGE_H

#include "dolphin/types.h"

class umbraStorage {
public:
    virtual int write(const void* data, u32 size) = 0;
    virtual int read(void* data, u32 size) = 0;
    virtual int remove() = 0;
    virtual ~umbraStorage() {}
};

class umbraStorageNintendont : public umbraStorage {
public:
    int write(const void* data, u32 size);
    int read(void* data, u32 size);
    int remove();
};

class umbraStorageMemcard : public umbraStorage {
public:
    umbraStorageMemcard(const char* filename) : mFilename(filename) {}
    int write(const void* data, u32 size);
    int read(void* data, u32 size);
    int remove();

private:
    const char* mFilename;
};

#endif // UMBRA_STORAGE_H
