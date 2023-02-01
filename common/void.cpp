#include <malloc.h>

#include <iostream>

void MyMalloc(void* ptr, int size) { ptr = malloc(size); }

void MyMalloc2(void** ptr, int size) { *ptr = malloc(size); }
void MyFree2(void** ptr) {
  free(*ptr);
  *ptr = nullptr;
}

int my_data = 10;
int other_data = 20;
int* my_pointer = &my_data;
// 通过传递指针的地址进行函数操作
void assign(void** ptr) { *ptr = &other_data; }

int main() {
  // int data = 20;
  char* ch_ptr = nullptr;
  MyMalloc(ch_ptr, 10);
  // Will lead to core dump
  // ch_ptr[0] = 'a';

  std::cout << "my pointer address is " << my_pointer << ", value is "
            << *my_pointer << std::endl;
  assign((void**)&my_pointer);
  std::cout << "After assign, my pointer address is " << my_pointer
            << ", value is " << *my_pointer << std::endl;

  char* p;
  // 直接将void*指针 强制转换为char *指针
  p = (char*)malloc(10);
  free(p);
  p = nullptr;

  int* int_ptr = nullptr;
  int int_num = 20;
  MyMalloc2((void**)&int_ptr, int_num * sizeof(int));
  for (int i = 0; i < int_num; i++) {
    int_ptr[i] = i;
  }
  for (int i = 0; i < int_num; i++) {
    std::cout << "int_ptr[" << i << "] is " << int_ptr[i] << std::endl;
  }
  MyFree2((void**)&int_ptr);
  return 0;
}