int numReaders = 0;
bool writerActive = false;
int writersWaiting = 0;
mutex_t lock;
cond_t unlockCalled;

void reader() {
  lock.lock();

  while (writerActive || writersWaiting > 0) {
    wait(unlockCalled, lock);
  }
  numReaders += 1;
  lock.unlock();
  
}

void writer() {
  lock.lock();

  writersWaiting += 1;
  while (numReaders > 0 || writerActive) {
    wait(unlockCalled, lock);
  }
  writerActive = true;
  writersWaiting -= 1;
  lock.unlock();
  
}

void unlock() {
  lock.lock();

  if (numReaders > 0) {
    numReaders -= 1;
  } else {
    writerActive = false;
  }

  broadcast(unlockCalled);
  lock.unlock();
  
}
