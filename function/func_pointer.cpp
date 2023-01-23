#include <iostream>
#include <string>

int AddFunc(int a, int b) { return (a + b); }

// Define a function pointer
typedef int (*p_func_add)(int, int);

typedef void (*FUNCTION)(void);

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

void OpenPrinter(void) { std::cout << "Open printer..." << std::endl; }

void InsertPaper(void) { std::cout << "Insert paper ..." << std::endl; }

void PrintPaper(void) { std::cout << "Print paper ..." << std::endl; }

void GetPaper(void) { std::cout << "Get paper ..." << std::endl; }

#define FUNC_COUNT 4
// callback function is a function which is called by the function pointer
int main() {
  p_func_add func_pointer = AddFunc;
  std::cout << "Sum is " << func_pointer(2, 4) << std::endl;

  struct printer {
    uint8_t func_count;
    FUNCTION func_array[FUNC_COUNT];
  } const printer_interface = {FUNC_COUNT,
                               {(FUNCTION)OpenPrinter, (FUNCTION)InsertPaper,
                                (FUNCTION)PrintPaper, (FUNCTION)GetPaper}};

  printer *printer_inst;
  printer_inst->func_array[0];
  printer_inst->func_array[1];
  Print(AddFunc, 2, 3);

  Timer(1, PrintCallback);

  return 0;
}