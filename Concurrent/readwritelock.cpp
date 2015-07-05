#include "readwritelock.h"

using namespace concurrent;
typedef std::unique_lock<std::mutex> UniqueLock;

ReadWriteLock::ThreadLockCounting* ReadWriteLock::threadLockCounting() {
    std::thread::id tid = std::this_thread::get_id();
    return this->threadMap.count(tid)>0 ?
                this->threadMap[tid] :
                (this->threadMap[tid]=new ThreadLockCounting());

}

void ReadWriteLock::lockForRead() {
    ThreadLockCounting* tlc = this->threadLockCounting();

    UniqueLock lock(mtx);
    while(!this->isClearForRead(tlc)) this->forRead.wait(lock);

    tlc->locks.push(READ_LOCK);
    tlc->readLockCount++;
    this->totalReadLockCount++;
}

void ReadWriteLock::lockForWrite() {
    ThreadLockCounting* tlc = this->threadLockCounting();

    UniqueLock lock(mtx);
    this->totalWaitingForWrite++;
    while(!this->isClearForWrite(tlc)) this->forWrite.wait(lock);
    this->totalWaitingForWrite--;

    tlc->locks.push(WRITE_LOCK);
    tlc->writeLockCount++;
    this->isLockedForWrite = true;
}

void ReadWriteLock::unlock() {
    ThreadLockCounting* tlc = this->threadLockCounting();

    UniqueLock lock(mtx);
    LockType locking = tlc->locks.top();
    tlc->locks.pop();
    if(locking==READ_LOCK) {

        // unlock a read lock;
        tlc->readLockCount--;
        if(--this->totalReadLockCount==0 && !this->isLockedForWrite && this->totalWaitingForWrite>0)
            this->forWrite.notify_one();

    } else {

        // unlock a write lock;
        if(--(tlc->writeLockCount)==0) {
            this->isLockedForWrite = false;
            if(this->totalWaitingForWrite>0) {
                if(!this->isLockedByMe(tlc))
                    this->forWrite.notify_one();
            } else {
                this->forRead.notify_all();
            }
        }
    }
}
