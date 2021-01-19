# Class

## 关键字

### private
- private修饰的变量只能由类的成员函数访问
- protected的作用和private类似

### public
- 类外部可以访问到的接口
- 一般在public定义函数，在private定义变量

```C++
class Box {
    public:
    // 构造函数
    Box(double l = 2.0, double h = 1.0, double w = 3.0) {
        length = l;
        height = h;
        width = w;
    };
    ~Box();

    double Volume {
        return (length * height * width);
    }

    int Comp(Box box) {
        return this.Volume() > box.Volume();
    }

    private:
    double length;
    double height;
    double width;
}
```

### virtual


## 函数
- 构造函数是特殊的成员函数
- 析构函数：类的特殊成员函数，删除类的对象时执行
  - 定义方式和构造函数完全相同，前面加~，不带返回值和参数

## new 和 delete
new和delte是C++的关键字，不是函数。
new和C中的malloc不一样，malloc是负责申请空间，不负责初始化；new可以负责初始化
```C++
string *psa = new string[10];      //array of 10 empty strings
int *pia = new int[10];           //array of 10 uninitialized ints
```

没有直接使用全局的new和delete，这种方法支持重载，如果没有重载，就是用全局的``::operator new`` 和 ``::operator delete``
```C++
Class A{};
A *element = new A;
delete element;
```

new执行分为两个阶段
1. 调用::operator new分配内存
2. 调用A::A()创建对象
   
delete实际执行的时候是分两个阶段
1. A::~A()析构对象
2. ::operator delete释放内存

new的重载
1. 返回值必须是void*
2. 可以使用多个参数，但是第一个参数必须是分配内存空间的大小（size_t）

```C++
void * operator new(size_t num) {
    cout << "Override new()" << endl;
    return ::operator new(num);
}
```

delete []是对申请的数组空间进行释放，和new []一起使用。下面的case只对数组的第一个元素析构
```
class A *pAa = new class A[3];
delete pAa;
```