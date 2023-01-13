cmake_minimum_required(VERSION 3.5)

project (thread_mutex)

set(SOURCES thread.cpp)

find_package(Threads REQUIRED)
add_executable(thread_mutex ${SOURCES})
set(THREADS_PREFER_PTHREAD_FLAG ON)
#set(CMAKE_CXX_FLAGS "-pthread")
target_link_libraries(thread_mutex PUBLIC Threads::Threads)

add_executable(promise_future promise_future.cpp)
target_link_libraries(promise_future PUBLIC Threads::Threads)