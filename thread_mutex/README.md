
# Thread Compilation

Ref: [Difference between -pthread and -lpthread while compiling](https://stackoverflow.com/questions/23250863/difference-between-pthread-and-lpthread-while-compiling)

If just compile the source code that involves the `thread`, you can use the command `g++ thread.cpp -o thread -lpthread`, where the -lpread should be placed at the end.

`-lpthread` is just a link option that explicitly points to the library that the generated object depends on.

`-pthread` tells the compliler to link the pthread library as well as configure the compilation for threads.

Since C++ 11, the standard thread library is introduced, but the implementation of the standard thread library is platform specific in GCC. For the Linux, std::thread is wrapped around the previous `pthread`.

# std::future

`std::future` is used to access the results of async operations that can be created by `std::async`, `std::packaged_task`, or `std::promise`. Therefore those operations are called the creators.

```C++
// future from a packaged_task
    std::packaged_task<int()> task([]{ return 7; }); // wrap the function
    std::future<int> f1 = task.get_future();  // get a future
```


# std::promise

`std::promise` is used to store a value or an exception that is later acquired via `std::future` object created by the `std::promise` object
`
In multi threads programming, `std::promise` works with the `std::future` to pass the values or objects among threads.
