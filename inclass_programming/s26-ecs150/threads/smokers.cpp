Table table; // assume set semantics
enum Item { papers, matches, tobacco };
mutex_t lock;
cond_t canSmoke;
cond_t doneSmoking;

// Smoking is a long operation and you can't hold the lock

// table has the following methods:
//  - isEmpty
//  - contains
//  - grabAllItems

// Good alternative solutions to practice:
//   - One condition variable
//   - Four condition variables, one per agent/smoker

void agent() {
  lock.lock();
  while (true) {

    while (!table.isEmpty()) {
      wait(doneSmoking, lock);
    }
    
    vector items = [papers, matches, tobacco];
    table.add(items.randomPop());
    table.add(items.randomPop());
    broadcast(canSmoke);

  }
  lock.unlock();
}

void smoker(Item myItem) {
  lock.lock();
  while (true) {

    // conditions to run
    //  - table is not empty && myItem not on the table
    //  - !table.isEmpty() && !table.contains(myItem)
    while (table.isEmpty() || table.contains(myItem)) {
      wait(canSmoke, lock);
    }
    
    vector items = [myItem];
    items.add(table.grabAllItems());
    lock.unlock();
    
    smoke(items);

    lock.lock();
    signal(doneSmoking);
  }
  lock.unlock();
}
