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
# 多态

动态多态 virtual
```C++
class A {
    public:
        virtual int f1() {
            return 0;
        }
        virtual void f2(){}
        void f3();
        virtual ~A(){ cout << "A";}

}

class B: public A{
    int f1() {return 1;} //重写
    virtual void f4(){}
    ~B(){ cout << "B";}
};
int main() {
    A *pa;
    pa = new B; // pa指向B类型对象
    pa -> f1(); //编译的时候忽略虚函数，执行的时候找到B的虚函数（动态链接）。派生类的函数覆盖了基类的虚函数
    delete pa; //如果class A中的析构函数没有virtal，析构的是A；如果添加virtual，析构的是B。析构的目的都是析构自己
}
```
64bit machine
sizeof(A) -> 8

A a;
a指向了a类的虚函数表，函数表为f1和f2，a的size为8byte
a -> A:f1 A:f2
B b;
b指向了父类(a)的虚函数表，b中有两个自己的函数表，其中B：f1重写了A：f1
b -> B:f1 A:f2 B:f4
B:f1覆盖了A：f1

多态
派生类的函数是否覆盖基类的虚函数
1. 函数名相同
2. 参数列表相同
3. 函数类型相同

虚函数调用时通过基类的指针或者引用，如
a->f1()

```
派生类对象 Square s(5, 6)
TwoDimensionShape *t = &s;
t->show()
//通过引用调用
void test(TwoDimensionShape &t) {
    t.show();
}
test(s);

```
如果基类的析构函数为virtual，所有派生类的析构函数都是virtual，也不需要注明为virtual

纯虚函数：没有函数体，只给出函数的原型。
```
virtual 函数类型 函数名（参数列表） = 0
virtual double getValue() = 0

```
>一个具有春旭函数的基类称之为抽象类
>抽象类不能被实例化，但可以声明抽象类的指针或者引用。所以用来定义规范
>
```
Square s(5, 6);
TwoDimensionShape *t1; //指针调用抽象类
t1 = &s;//指向子类对象
cout<< "面积为" << t1->getArea()<<endl;//多态的表现，指向父类的指针调用子类的成员函数
```