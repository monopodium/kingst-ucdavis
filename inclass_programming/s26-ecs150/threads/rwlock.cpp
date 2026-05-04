int numReaders = 0;
bool writerActive = false;
mutex_t lock;
cond_t unlockCalled;

void reader() {
  lock.lock();
  while (writerActive) {
    wait(unlockCalled, lock);
  }
  numReaders += 1;
  lock.unlock();
}

void writer() {
  lock.lock();
  while (numReaders > 0) {
    wait(unlockCalled, lock);
  }
  writerActive = true;
  lock.unlock();
}

void rwunlock() {
  lock.lock();
  if (numReaders > 0) {
    numReader -= 1;
  } else {
    writerActive = false;
  }
  broadcast(unlockCalled);
  lock.unlock();
}
