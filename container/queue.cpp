#include <iostream>
#include <queue>

int main() {
  std::queue<int> q;
  std::queue<int> data_queue({3, 4, 5, 6});
  std::queue<int> new_queue(std::move(data_queue));

  std::cout << "The last element from the new_queue is " << new_queue.back()
            << std::endl;

  for (int i = 0; i < 5; i++) {
    q.push(i);
  }

  while (!q.empty()) {
    int value = q.front();
    std::cout << "The data pops from the queue is " << value << std::endl;
    q.pop();
  }

  return 0;
}