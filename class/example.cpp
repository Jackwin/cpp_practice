#include<iostream>
using namespace std;

class TwoDimensionShape {
public:
    TwoDimensionShape();

    virtual ~TwoDimensionShape();
    virtual double getArea() = 0;
    virtual void show() = 0;
};
TwoDimensionShape::TwoDimensionShape() {
    cout << "二维形状构造函数" << endl;
}
TwoDimensionShape::~TwoDimensionShape() {
    cout << "二维形状析造函数" << endl;
}
class Square: public TwoDimensionShape {
private:
    double side;
public:
    Square(double);
    ~Square();
    double getArea();
    void show();

};

Square:: Square(double side): side(side) {
    cout << "正方形构造函数" << endl;
}
Square:: ~Square(){
    cout << "正方形析构函数" << endl;
}
double Square:: getArea() {
    return side * side;
}

void Square:: show() {
    cout << "正方向边长为" << side << endl;
}

int main() {
    Square s(10.0);
    TwoDimensionShape *pt = &s;
    cout << "面积为" << pt->getArea() <<endl;
    pt->show();

    return 0;
}