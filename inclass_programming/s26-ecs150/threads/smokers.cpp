Table table; // assume set semantics
enum Item { papers, matches, tobacco };

// Smoking is a long operation and you can't hold the lock

// table has the following methods:
//  - isEmpty
//  - contains
//  - grabAllItems

// Good alternative solutions to practice:
//   - One condition variable
//   - Four condition variables, one per agent/smoker

void agent() {
  while (true) {

    vector items = [papers, matches, tobacco];
    table.add(items.randomPop());
    table.add(items.randomPop());

  }
}

void smoker(Item myItem) {
  while (true) {

    vector items = [myItem];
    items.add(table.grabAllItems());

    smoke(items);

  }
}
