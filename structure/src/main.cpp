
#include <iostream>

#include "struct_example.hpp"

int main() {
  //   DataGeneratorParam::DataGeneratorParam(int num) {
  // 	  for(int i = 0; i < num; i++) {
  // 	  cout << ""The data genearated is "" << i <<endl;
  // }
  // DataGeneratorParam::DataGeneratorParam(8);
  std::string my_name = "Jack";
  std::string friend_name = "Jane";
  std::string city = "Beijing";

  CoffeeMachine coffee_machine;
  coffee_machine.operator_name = "Jack";
  coffee_machine.coffee_type = "Latte";

  Coffee latte(2, 5);
  coffee_machine.func = make_coffee;
  coffee_machine.func(coffee_machine, latte);
  coffee_machine.func = warm_milk;
  coffee_machine.func(coffee_machine, latte);

  // Construct the structure with parameters
  /*
  Person jack(10, 20, my_name, friend_name, city);
  jack.printName();
  int x = jack.getAge();
  std::cout << "The age of Jack is " << x << std::endl;
  jack.greet();

  // Constuct the structure without parameters
  Person jim = {11, 21, "Jim", "Tom", "Shanghai"};
  int jim_age = jim.getAge();
  std::cout <<  "The age of jim is " << x << std::endl;
  jim.greet();

  hello hi;
  hi.print();
  return 0;
  */
}
