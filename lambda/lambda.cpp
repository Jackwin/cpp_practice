#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

int main() {
  int a = 2;
  int x = 9;

  // When the lambda function is created, a has captured the value by the copy
  // assignment
  auto increase_value = [a](int x) { return (a + x); };

  a = 10;
  x = 20;
  // The lastet a assigment does not affect the lambda, but x will pass the
  // latest value
  auto data = increase_value(x);

  std::cout << "Value capture: data is " << data << std::endl;

  // Update b value via the reference capture
  int b = 10;
  auto update_value = [&b](int x) { b = b + x; };

  update_value(x);
  std::cout << "Reference capture: b is updated to " << b << std::endl;

  auto print_variables = [=] {
    std::cout << "capture all the variables via value capture: a is " << a
              << std::endl;
    std::cout << "capture all the variables via value capture: b is " << b
              << std::endl;
  };

  print_variables();

  // C++ 14 feature
  auto groud_truth = std::make_unique<int>(10);
  auto scale = [factor = 2, data = std::move(groud_truth)] {
    return (factor * (*data));
  };

  auto ground_truth_scale = scale();
  std::cout << "ground_truth is scaled to " << ground_truth_scale << std::endl;

  struct Coordinate {
    Coordinate(float x_axis, float y_axis) : x(x_axis), y(y_axis) {}
    float x;
    float y;
  };

  // Lambda used in STL algorithm
  std::vector<Coordinate> coord_vec;
  coord_vec.emplace_back(Coordinate(1.0, 2.0));
  coord_vec.emplace_back(Coordinate(3.0, 4.0));
  coord_vec.emplace_back(Coordinate(2.0, 5.0));

  std::sort(
      coord_vec.begin(), coord_vec.end(),
      [](const Coordinate &c1, const Coordinate &c2) { return (c1.x < c2.x); });

  std::for_each(coord_vec.begin(), coord_vec.end(), [](const Coordinate &c) {
    std::cout << "The coordinate is (" << c.x << "," << c.y << ")" << std::endl;
  });
  return 0;
}