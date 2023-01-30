#include <assert.h>
#include <unistd.h>

#include <chrono>
#include <iostream>

#define MY_ASSERT(condition, ...) assert(condition)

#define _MY_ASSERT_COM(x, op, y, ...) MY_ASSERT(((x)op(y)), __VA_ARGS__)

#define MY_ASSERT_EQ(x, y, ...) _MY_ASSERT_COM(x, ==, y, __VA_ARGS__)
#define MY_ASSERT_NE(x, y, ...) _MY_ASSERT_COM(x, !=, y, __VA_ARGS__)
#define MY_ASSERT_LE(x, y, ...) _MY_ASSERT_COM(x, <=, y, __VA_ARGS__)
#define MY_ASSERT_LT(x, y, ...) _MY_ASSERT_COM(x, <, y, __VA_ARGS__)
#define MY_ASSERT_GE(x, y, ...) _MY_ASSERT_COM(x, >=, y, __VA_ARGS__)
#define MY_ASSERT_GT(x, y, ...) _MY_ASSERT_COM(x, >, y, __VA_ARGS__)

#define PRINT(FORMAT, VALUE) \
  printf("The value of" #VALUE " is " FORMAT "\n", VALUE)

#define APPLE_PRICE 3
#define BANANA_PRICE 4
#define PRINT_VALUE(PREFIX, FORMAT) \
  printf("The price is " FORMAT "\n", PREFIX##_PRICE)

#define TO_STRING(x) #x

//#define PRINT_HELLO(type_prefix, data) type_prefix

#define PROFILE_CPU(name, code_block) \
  do {                                \
    code_block;                       \
  } while (0)

#define MY_PRINTF(name, ...) printf(name, __VA_ARGS__)

class Clock {
 public:
  virtual void Start() = 0;
  virtual uint64_t End() = 0;
};

class CpuClock : public Clock {
 public:
  void Start() { _start = std::chrono::steady_clock::now(); }

  uint64_t End() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - _start)
        .count();
  }

 private:
  std::chrono::steady_clock::time_point _start;
};

void start(std::string str, CpuClock &cpu_clock) {
  // std::cout << str << " " << counter << std::endl;
  std::cout << str << " timer starts" << std::endl;
  cpu_clock.Start();
}

void end(std::string str, CpuClock &cpu_clock) {
  std::cout << str << " end." << std::endl;
  std::cout << "The elapse time is " << cpu_clock.End() << " ms" << std::endl;
}

#define MY_TIMER(name, code_block, ...) \
  do {                                  \
    start(name, __VA_ARGS__);           \
    code_block;                         \
    end(name, __VA_ARGS__);             \
  } while (0)

int main() {
  int i = 9;
  MY_ASSERT(i == 9);
  int j = 8;
  MY_ASSERT_GT(i, j);

  for (int k = 0; k < 5; k++) {
    PROFILE_CPU("sleep", { usleep(1000); });
    std::cout << "sleep " << k << std::endl;
  }

  MY_PRINTF("my printf: i = %d, j = %d\n", i, j);

  CpuClock cpu_clock;

  MY_TIMER(
      "my timer", { usleep(1000); }, cpu_clock);

  int x = 9;
  PRINT("%d", x + 2);

  std::cout << "The string is " << TO_STRING(1224) << std::endl;

  PRINT_VALUE(APPLE, "%d");
  PRINT_VALUE(BANANA, "%d");

  return 0;
}