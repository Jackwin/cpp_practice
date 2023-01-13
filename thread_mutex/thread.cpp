#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <functional>

void counter(){
  for(int i = 0; i < 5; i++) {
    std::cout << "The counter from thread " << "is " << i << std::endl;
    }
}
using namespace std;
class ThreadPool {
  public:
    std::function<void()> _func;
    ThreadPool(size_t thread_num):_thread_num(thread_num){
      _thread_pool.resize(_thread_num);
    }
    ~ThreadPool(){}

    void print_hello(){
      printf("hello\n");
    }

  private:
    size_t _thread_num;
    std::vector<std::thread> _thread_pool;
    std::function<void()> _tasks;
};

int main() {
  //MyThread *thread1 = new MyThread();
  //thread1->job_run();
     std::thread th1(counter);
  th1.join();
  //MyThread thread1(counter);
  return 0;
}
