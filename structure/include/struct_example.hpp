
#ifndef STRUCT_EXAMPLE_H
#define STRUCT_EXAMPLE_H
#include <string>
#include <iostream>
using namespace std;

struct Person {
  int num;
  int age;
  std::string my_name;
  std::string friend_name;
  std::string city;
	 
  //Person() : age(20){} // a constructor
  // member function inside structure
  int getAge() {
    return age;
  }
  void printName();

  // Cosntruct the structure with parameters
  Person(int num, int age, string my_name, string friend_name, string city):
  num(num),
  age(age),
  my_name(my_name),
  friend_name(friend_name),
  city(city){}

  // Construct the structure without parameters
  Person() :num(), age(), my_name(), friend_name(), city(){}

	//void DataGeneratorParam (int cnt, string name);
	void greet() {
    cout << my_name << ", welcome " << friend_name << endl;
  };

};

void Person::printName() {
  cout << "My name is " << my_name << endl;
}

class hello {
	public:
		void print();
};

void hello::print() {
	cout << "hello world" << endl;
}

#endif