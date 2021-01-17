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