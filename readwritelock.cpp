#include "readwritelock.h"

ReadWriteLock::ThreadLockCounting* ReadWriteLock::threadLockCounting() {
    std::thread::id tid = std::this_thread::get_id();
    return this->threadMap.count(tid)>0 ?
                this->threadMap[tid] :
                (this->threadMap[tid]=new ThreadLockCounting());

}

void ReadWriteLock::lockForRead() {
    ThreadLockCounting* tlc = this->threadLockCounting();

    std::unique_lock<std::mutex> lock(this->mutex);
    while(!this->isClearForRead(tlc)) this->forRead.wait(lock);

    tlc->locks.push(READ_LOCK);
    tlc->readLockCount++;
    this->totalReadLockCount++;
}

void ReadWriteLock::lockForWrite() {
    ThreadLockCounting* tlc = this->threadLockCounting();

    std::unique_lock<std::mutex> lock(mutex);
    this->totalWaitingForWrite++;
    while(!this->isClearForWrite(tlc)) this->forWrite.wait(lock);
    this->totalWaitingForWrite--;

    tlc->locks.push(WRITE_LOCK);
    tlc->writeLockCount++;
    this->isLockedForWrite = true;
}

void ReadWriteLock::unlock() {
    ThreadLockCounting* tlc = this->threadLockCounting();

    std::unique_lock<std::mutex> lock(mutex);
    LockType locking = tlc->locks.top();
    tlc->locks.pop();
    if(locking==READ_LOCK) {

        tlc->readLockCount--;
        if(--this->totalReadLockCount==0 && !this->isLockedForWrite && this->totalWaitingForWrite>0)
            this->forWrite.notify_one();

    } else {

        if(--tlc->writeLockCount==0) {
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
