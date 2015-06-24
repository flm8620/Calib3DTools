#ifndef READWRITELOCK_H
#define READWRITELOCK_H

#include <stack>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace concurrent {

using std::mutex;
using std::condition_variable;
using std::stack;
using std::map;

class ReadWriteLock
{
public:
    void lockForRead();
    void lockForWrite();
    void unlock();

private:
    typedef enum { READ_LOCK, WRITE_LOCK } LockType;
    typedef struct {
        stack<LockType> locks;
        int readLockCount=0, writeLockCount=0;
    } ThreadLockCounting;

    map<std::thread::id, ThreadLockCounting*> threadMap;

    int totalReadLockCount = 0;
    int totalWaitingForWrite = 0;
    bool isLockedForWrite = false;
    mutex mtx;
    condition_variable forRead;
    condition_variable forWrite;

    ThreadLockCounting* threadLockCounting();
    inline bool isLockedForWriteByAnother(ThreadLockCounting* th) {
        return this->isLockedForWrite && th->writeLockCount<=0;
    }

    inline bool isLockedForReadByAnother(ThreadLockCounting* th) {
        return th->readLockCount<this->totalReadLockCount;
    }

    inline bool isLockedByMe(ThreadLockCounting* th) {
        return th->readLockCount>0 || th->writeLockCount>0;
    }

    inline bool isClearForRead(ThreadLockCounting* th) {
        return isLockedByMe(th) || ( !isLockedForWriteByAnother(th) && this->totalWaitingForWrite<=0 );
    }

    inline bool isClearForWrite(ThreadLockCounting* th) {
        return !isLockedForReadByAnother(th) && !isLockedForWriteByAnother(th);
    }
};

class ReadLock
{
private:
    ReadWriteLock& rwLock;
    bool isLocked;
public:
    ReadLock(ReadWriteLock& rwLock) : rwLock(rwLock) {
        this->rwLock.lockForRead();
        this->isLocked = true;
    }

    void unlock() {
        if(this->isLocked) {
            this->rwLock.unlock();
            this->isLocked = false;
        }
    }

    void relock() {
        if(!this->isLocked) {
            this->rwLock.lockForRead();
            this->isLocked = true;
        }
    }

    ~ReadLock() { this->unlock(); }
};


class WriteLock
{
private:
    ReadWriteLock& rwLock;
    bool isLocked;
public:
    WriteLock(ReadWriteLock& rwLock) : rwLock(rwLock) {
        this->rwLock.lockForWrite();
        this->isLocked = true;
    }

    void unlock() {
        if(this->isLocked) {
            this->rwLock.unlock();
            this->isLocked = false;
        }
    }

    void relock() {
        if(!this->isLocked) {
            this->rwLock.lockForWrite();
            this->isLocked = true;
        }
    }

    ~WriteLock() { this->unlock(); }
};

} //namespace concurrent
#endif // READWRITELOCK_H
