#include <iostream>
#include <future>
#include <chrono>
#include <string>
#include <thread>

void ping(std::promise<std::string> &p) {

  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::string str = "Ping";
  std::cout << str << std::endl;
  p.set_value(str);
}


void pong(std::future<std::string> &f) {
  auto value = f.get();
  if (value == "Ping")
    std::cout << "Pong" << std::endl;
}

int main() {

  std::promise<std::string> p1;
  std::future<std::string> f1 = p1.get_future();

  std::thread th1(ping, std::ref(p1));
  std::thread th2(pong, std::ref(f1));
  th1.join();
  th2.join();

  return 0;
}