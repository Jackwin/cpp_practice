#include <algorithm>
#include <deque>
#include <iostream>

template <typename T>
void PrintDeque(const T& deque, const std::string& str) {
  std::cout << str;
  for (auto it : deque) {
    std::cout << it << " ";
  }
  std::cout << std::endl;

  std::cout << "****************" << std::endl;
}

int main() {
  int element_num = 10;
  std::deque<int> deq1(10, 5);
  std::deque<int> deq2(deq1);

  for (int i = 0; i < element_num; i++) {
    deq1.push_back(i);
  }

  deq1.push_front(100);
  PrintDeque(deq1, "The original deque is ");
  deq1.erase(deq1.begin() + 2, deq1.begin() + 5);
  PrintDeque(deq1, "The deque after erasing [2, 5] is ");

  std::sort(deq1.begin(), deq1.end());
  PrintDeque(deq1, "The deuqe after sorting is ");

  deq1.pop_front();
  deq1.pop_back();
  PrintDeque(deq1, "The deque after front and pop is ");
  return 0;
}