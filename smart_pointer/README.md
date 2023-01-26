# 智能指针

智能指针采用RAII原则，在构造函数中申请内存，在析构函数中释放内存，避免内存泄漏。

智能指针采用对引用对象进行计数的方式来管理内存的释放，对于内存的对象每引用一次，计数便加一，每删除一次引用，计数便减一，当计数为0时，自动释放对象的内存空间

# shared_ptr
shared_ptr， unique_ptr和weak_ptr的使用需要包含头文件\<memory>

std::shared_ptr 可以和其他pointer共享一个对象，unique_ptr不能和其他pointer共享对象。所以unique_ptr使用场景是当对象只被一个所有者所有。

`shared_ptr` 使用`get()`获得原始指针，`reset()`减少一次计数，`use_count(）`  查看一个对象的引用次数

`std:: shared_ptr` 仍然需要使用new来调用，代码出现不对称。C++14之后，可以使用std::make_shared 消除显示得使用new来调用，std::make_shared会分配创建传入参数的对象，并放回该对象类型的s`td:shared_ptr`

std::shared_ptr的用法一般是 `std::shared_ptr<A> sp1(new A())`; 

创建智能指针std::shared_ptr\<A> sp1(); 然后智能指针指向对象A

```cpp
A * pA = new A();
std::shared_ptr<A> spA(pA);
```

shared_ptr可以继承`std::enable_shared_from_this` 用于返回this的一个std::shared_ptr对象给外部使用。本质就是返回其他shared_ptr对象的实例，

# unique_ptr
某个时刻，unique_ptr指向一个给定对象，对其拥有的堆内存具有唯一控制权， 引用计数始终为1，禁止和其他智能指针使用同一对象，保证代码安全

当unique_ptr被销毁时，指向的对象也被销毁

unique_ptr不支持拷贝构造函数，就是不能一个unique_ptr赋值给另外的unique_ptr，可以通过移动机制将指针的所有从一个unique_ptr转移到另外一个unique_ptr，转移使用std::move

unique_ptr不支持拷贝构造和赋值运算符，参考其类的定义，只能使用移动构造。unique_ptr是位于堆内存
```C++
template <class T>
class unique_ptr {
unique_ptr(const unique_ptr &) = delete; // copy construct forbidden
unique_ptr & operator = (const unique_ptr &) =delete; 赋值运算符
}

int main() {
std::unique_ptr<int> unique_ptr1(std::make_unique<int>(15)); //指向一个堆对象
std::unique_ptr<int> unique_ptr2(std::move(unique_ptr1)); 使用std:move移动构造

std:: unique_ptr<int []> p1(std::make_unique<int[]>(8)); 指向一组堆对象

```