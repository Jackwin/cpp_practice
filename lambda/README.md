# Lambda

lambda的方便之处在于通过匿名函数随时定义函数，不需要考虑定义函数名再定义函数，常用于临时函数，减轻函数的数量，代码清晰可读

lambda函数体内部不能使用外部的变量，因此通过捕捉列表的方式将需要的外部变量传到lambda函数的内部。

\[ ]指的是闭包，对于Lambda函数之外声明的变量，这些变量的集合称之为闭包，Lambda函数通过捕捉的方式引用这些变量

\[capture](parameters) mutable ->return-type{statement};

1. \[ ] 捕捉列表，也是lambda的标识，编译器根据此符号判断是否是Lambda函数。捕捉列表能够获取到上下文的变量供Lambda使用
    1. [Var] 值传递方式捕捉变量var，值捕获的前提是变量可以拷贝，也就是说值捕获是通过变量拷贝实现的。值捕获是在lambda表达式创建的时候进行拷贝，而不是在调用的时候拷贝
    ```C++
    int main() {
    int a = 2;
    int x = 9;
    // 创建lambda函数时，a已经通过值捕获的方式得到赋值
    auto increase_value = [a](int x) { return (a + x); };
    a = 10;
    x = 20;
    // a虽然被赋值为10，但在使用lambda函数时，a仍然为2
    auto data = increase_value(x);
    std::cout << "Value capture: data is " << data << std::endl;
   ```
    2. [&] 引用传递方式捕捉所有父作用域的变量
    3. [& var] 标识引用传递捕捉变量var
    4. [=] 值传递方式捕捉所有父作用域的变量
    5. [=,&a,&b]表示以引用传递的方式捕捉变量a和b，以值传递方式捕捉其它所有变量
2. (parameters) 参数列表，与普通函数参数列表一致，没有参数可以省略括号
3. mutable 修饰符，Lambda函数总是一个const函数，mutable可以取消其常量性
4. ->return-type：返回类型，没有返回值可以省略
5. {statement}：函数体,在中括号的最后添加；


C++14 允许捕获的成员使用任意方式初始化，比如在捕获列表中进行赋值，以及使用右值捕获，被声明的捕获变量类型会根据表达式进行判断，判断方式与使用 auto 本质上是相同的