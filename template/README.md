# Template（draft）

Ref: [CppTemplateTutorial](https://github.com/wuye9036/CppTemplateTutorial)

## 常见的替换方法
1. 宏定义，问题不知道类型
    ```C++
    #define Comp(a, b) (a < b ? a : b)
   ```
2. 重载： 需要多种重载版本，不支持新的类型
3. 模板：支持新类型。
    ```C++
    //函数模板
    template <typename T> T Comp (T a, T b){
        return (a < b ? a : b);
    } 

    // Compiling genearation 模板函数
    int Comp (int a, int b){
        return (a < b ? a : b);
    ```
    - 编译的过程是先找函数，再找模板特化，再找模板；编译完成后没有模板，模板变成了函数
    - 如果没调用函数模板，那么模板不参与编译；如果是以函数编写，即使不调用，编译的时候也会生成，占用一定的内存空间

## 模板使用的问题
1. 模板的参数虽然是变化的，但在编译器件是确定的，因此在编译之前需要确保模板参数是确定的

## Template
1. 模板适用的场景是处理的数据类型不同，但实现的功能（业务逻辑）相同
2. 模板分为函数模板和类模板
    - 类模板： 主要用于数据存储（容器），实现的算法不受数据类型的影响
    - 类模板的成员函数都是函数模板
3. 如果一个函数使用类模板参数，那么该函数一定是函数模板,函数的实参是模板实例化的模板类对象
    ```C++
    template <typename T> class Array;
    template <typename T> T Foo(Array<T>& a) {}

    Array<float> FloatArray(2);
    Foo(FloatArray)

    ```

Template Class 声明
```c++
//statement typename T 是类型参数
template <typename T> class ClassAnimal;
// definition
template <typename T> class ClassAnimal {
    T member;
    public:
        void give
};
```

Template function
```C++
template <typename T> T GetName(ClassAnimal<T> AnyAnimal) {
    return <T> AnyAnimal.member;
}
```

Template参数可以是基本类型，结构，类类型，也可以是整型数(Integral Number)包括布尔，有符号无符号的整型数，指针。

*Note：只有整型可以作为模板参数，float不行*

整型模板参数的基本用途是定义一个常量
```C++
template <typename T, int size> struct Vector {
    T data[size];
}

Vector<int, 16> vec;
```

```C++
template <int i> class A {
    public:
        void foo(int) {};
}

template <int i, int j> int Add {
    return (i + j);
}

// 模板参数无符号，指针类型
template <uint8_t a, typename b, void* c> class B {}; 
//模板参数为任意函数指针
template <bool, void (*a)()> class C {};
// 模板参数为成员函数指针，函数形参为int
template <void (A<3>::*a)(int)> class D {};

void foo1 {
    int* ptr = nullptr;
    A<8> a;
    B<2, A<8>, ptr> b;
    C<true, &Add> c;
    D<&A<3>::foo> d;
    C<true, &A<3>::foo> c1; // 也可以吧？都是函数指针

}

```

## 可变参数模板/函数

C++ 11 开始，模板允许有0个或者多个模板参数，可变模板参数的表示使用 `...`
在下文中,`... args`组成了可变模板参数

```C++
template<typename... T> class MyTemplate;

MyTemplate<int, float, std::vector<int>> my_temp_instance;

MyTemplate<> my_temp_instance2;
```

省略号的使用
1. 放在形参的左边，如上述的模板可变参数，表示声明了一个参数包(parameter pack)，可以绑定0个或者多个模板参数


函数中也可以使用可变参数，比较典型的应用是打印函数
```C++
void func(const T& t, const Args&... args);
```

`sizeof...()`用于获得模板参数包或者函数参数包的参数个数

## 元编程

元编程有种“隔山打虎的意思”，打的是山，实际目标是虎，打山的过程是元编程，起到打老虎的作用是元程序。

程序语言理解：编写一段源程序A，编译生成了程序B，B实际起到作用。抽象理解为：抽象了程序A，具体化了程序B。

C++中元编程的手段可以是宏，也可以模板

函数重写也有替换的功能

## 特化
特化(specilization) 部分特化(partial specialization)

特化：是对已有的模板具体化，理解为一套模板可以干N中事情，增加特化，指定具体干什么，比如一个两个参数的模板函数,可以抽象的表示很多行为，比如a+b, a*b, a/b等等，通过特化的方式指定模板的行为
```C++
//原型
template <T typename1> class A{}
// 特化 此处的int取代了原型中的T
template <> class A<int>
```

```C++
//定义一个原型的模板
template <typename T> class AddFloatOrMulInt{
    static T foo(T a, T b) {
        return (0); //此处无所谓，代码用不到
    }
}
template <> class AddFloatOrMulInt <int>{
    static int foo(int a, int b) {
        return (a + b); 
    }
}

template <> class AddFloatOrMulInt <float>{
    static float foo(float a, float b) {
        return (a * b); 
    }
}

```

偏特化和特化的不同之处似乎在形式上看偏特化的第一个<>需要指定类型；偏特化的参数个数必须和原型的参数个数一致
```C++
template <typename T> class AddFloatOrMulInt ;

template <typename T> class AddFloatOrMulInt <int>;

template <typename T, typaname U> class X;
template <typename T> class X <T, T> {};

// 下面的偏特化有问题，偏特化的参数个数不同
template <typename T> struct DoWork;
template <> struct DoWork<int, int> {};  

```

支持参数长度不一样的偏特化
1. 模板参数多，使用void表示参数可有可无
    ```C++
    template <typename T0, typename T1 = void> struct DoWork;
    template <>           struct DoWork<int> {};
    Dowork<int> i;
    ```
2. 使用变参模板(Variadic Template) , Ts不定长的参数列表
    ```C++
    template <typename... Ts> class tuple;
    // 以下原型的表达错误，作为原型 Ts需要放在模板参数的最后面，C++匹配是自左向右
    template <typename... Ts, typename U> class X {}; //(1)
    // (1)修改为
    template < typename U, typename... Ts> class X {}; //(2)

    // Y的原型 
    template <typename... Ts>             class Y {};              // (3)
    // (4)不同于(1) 在于(4)是偏特化，Ts不用在尾部。模板类型仅仅代表类型，为偏特化的模式提供的声明，没有顺序之分，匹配顺序按照U Ts
    template <typename... Ts, typename U> class Y<U, Ts...> {};    // (4)
    ```
