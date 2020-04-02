#include <algorithm>
#include <iostream>

struct Node {
  int value;
  struct Node* next;
};

struct Node* cycleStart(struct Node* head) {
  if (head == nullptr || head->next == nullptr) {
    return nullptr;
  }

  Node* fast_ptr = head->next->next;
  Node* slow_ptr = head->next;

  while (fast_ptr != slow_ptr) {
    if (fast_ptr == nullptr || fast_ptr->next == nullptr) {
      return nullptr;
    }

    fast_ptr = fast_ptr->next->next;
    slow_ptr = slow_ptr->next;
  }

  slow_ptr = head;
  while (slow_ptr != fast_ptr) {
    slow_ptr = slow_ptr->next;
    fast_ptr = fast_ptr->next;
  }
  return slow_ptr;
}

void addNode(struct Node* current, int value) {
  Node* node = new Node;
  node->next = current->next;
  node->value = value;
  current->next = node;
}

Node* NonCycledList(int number_of_elements) {
  Node* head = new Node;
  head->next = nullptr;
  head->value = 0;

  Node* current = head;
  for (int i = 1; i < number_of_elements; ++i) {
    addNode(current, i);
    current = current->next;
  }

  return head;
}

std::pair<Node*, Node*> CycledList(int num_nodes_before_cycle,
                                   int num_nodes_in_cycle) {
  Node* head = NonCycledList(num_nodes_before_cycle + num_nodes_in_cycle);
  Node* current = head;

  int counter = 1;
  Node* cycle_beginning = nullptr;
  while (current->next != nullptr) {
    if (counter == num_nodes_before_cycle) {
      cycle_beginning = current->next;
    }

    current = current->next;
    ++counter;
  }

  current->next = cycle_beginning;

  return std::make_pair(head, cycle_beginning);
}

int main() {
  Node* non_cycled_list = NonCycledList(1);
  std::cout << (cycleStart(non_cycled_list) == nullptr);

  non_cycled_list = NonCycledList(2);
  std::cout << (cycleStart(non_cycled_list) == nullptr);

  non_cycled_list = NonCycledList(10);
  std::cout << (cycleStart(non_cycled_list) == nullptr);

  non_cycled_list = NonCycledList(11);
  std::cout << (cycleStart(non_cycled_list) == nullptr);

  auto cycled_list = CycledList(1, 1);
  std::cout << (cycleStart(cycled_list.first) == cycled_list.second);

  cycled_list = CycledList(2, 1);
  std::cout << (cycleStart(cycled_list.first) == cycled_list.second);

  cycled_list = CycledList(1, 2);
  std::cout << (cycleStart(cycled_list.first) == cycled_list.second);

  cycled_list = CycledList(2, 2);
  std::cout << (cycleStart(cycled_list.first) == cycled_list.second);

  cycled_list = CycledList(4, 5);
  std::cout << (cycleStart(cycled_list.first) == cycled_list.second);

  cycled_list = CycledList(5, 4);
  std::cout << (cycleStart(cycled_list.first) == cycled_list.second);

  return 0;
}
