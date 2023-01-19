#include <iostream>
#include <string>

int AddFunc(int a, int b) { return (a + b); }

// Define a function pointer
typedef int (*p_func_add)(int, int);

//  function pointer as the function parameter
void Print(p_func_add func, int a, int b) {
  std::cout << " the result is " << func(a, b) << std::endl;
}

void PrintCallback(void) {
  std::cout << "From callback function " << std::endl;
}

void Timer(int data, void (*prinf_call_back)(void)) {
  if (data == 1) {
    PrintCallback();
  }
}

// callback function is a function which is called by the function pointer
int main() {
  p_func_add func_pointer = AddFunc;
  std::cout << "Sum is " << func_pointer(2, 4) << std::endl;

  Print(AddFunc, 2, 3);

  Timer(1, PrintCallback);

  return 0;
}