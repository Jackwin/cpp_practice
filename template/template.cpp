#include <iostream>
using namespace std;
template <typename T>
class TypetoId {
 public:
  static int const ID = -1;
};

template <>
class TypetoId<int8_t> {
 public:
  static int const ID = 0;
};

// pointer specilization
template <>
class TypetoId<void*> {
 public:
  static int const ID = 0x1234;
};
// array specilization
template <>
class TypetoId<int[4]> {
 public:
  static int const ID = 0x1235;
};

// 类模板练习
// 实现的功能数据顺序进入，顺序读出

template <typename T>
class Array {
 public:
  Array(int s);
  virtual ~Array();
  T& Entry(int index);
  void Enter(int index, const T& value);
  // protected 变量在构造函数中赋值
 protected:
  int size;
  T* element;
};

template <typename T>
Array<T>::Array(int s) {
  size = s;
  element = new T[size];
}

template <typename T>
Array<T>::~Array() {
  delete[] element;
}

template <typename T>
T& Array<T>::Entry(int index) {
  return element[index];
}

template <typename T>
void Array<T>::Enter(int index, const T& value) {
  element[index] = value;
}

int main() {
  TypetoId<int8_t> A;
  TypetoId<int16_t> B;
  TypetoId<void*> C;
  std::cout << "ID of int8_t " << A.ID << endl;
  std::cout << "ID of int16_t " << B.ID << endl;
  std::cout << "ID of void* " << TypetoId<void*>::ID << endl;
  std::cout << "ID of int[4] " << TypetoId<int[4]>::ID << endl;

  Array<int> D(5);
  for (int i = 0; i < 4; i++) D.Enter(i, i);
  for (int i = 0; i < 4; i++) {
    std::cout << D.Entry(i) << endl;
  }

  return 0;
}
