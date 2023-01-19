#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

void counter() {
  for (int i = 0; i < 5; i++) {
    std::cout << "The counter from thread "
              << "is " << i << std::endl;
  }
}

std::mutex mt;
std::mutex g_mutex;

void ping() {
  for (int i = 0; i < 5; i++) {
    mt.lock();
    std::cout << "Ping" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mt.unlock();
  }
}

void pong() {
  for (int i = 0; i < 5; i++) {
    if (mt.try_lock()) {
      std::cout << "Pong" << std::endl;
      mt.unlock();
    }
  }
}

int g_counter = 0;
void Counter() {
  std::lock_guard<std::mutex> lock(g_mutex);
  g_counter++;
  std::cout << "Counter is " << g_counter << std::endl;
}

using namespace std;
class ThreadPool {
 public:
  std::function<void()> _func;
  ThreadPool(size_t thread_num) : _thread_num(thread_num) {
    _thread_pool.resize(_thread_num);
  }
  ~ThreadPool() {}

  void print_hello() { printf("hello\n"); }

 private:
  size_t _thread_num;
  std::vector<std::thread> _thread_pool;
  std::function<void()> _tasks;
};

int main() {
  // MyThread *thread1 = new MyThread();
  // thread1->job_run();
  std::thread th1(counter);
  th1.join();

  std::thread thread_ping(ping);
  std::thread thread_pong(pong);
  thread_ping.join();
  thread_pong.join();

  int thread_num = 4;
  std::vector<std::thread> thread_vec;
  thread_vec.reserve(4);

  for (int i = 0; i < thread_num; i++) {
    thread_vec.emplace_back(Counter);
  }

  for (auto &it : thread_vec) {
    it.join();
  }

  // MyThread thread1(counter);
  return 0;
}
