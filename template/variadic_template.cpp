#include <iostream>
#include <string>
#include <vector>
template <typename T, typename... Args>
void print_size(const T& t, const Args&... args) {
  std::cout << sizeof(t) << std::endl;
  // sizeof...() to get the number of the parameter pack
  std::cout << sizeof...(args) << std::endl;
}

int main() {
  int data = 4;
  std::string str = "hello";
  std::vector<int> vec(4, 1);
  print_size(data, str, vec);
  // The number of the parameter pack is 3, including data, data, and str
  print_size(str, data, data, str);

  return 0;
}