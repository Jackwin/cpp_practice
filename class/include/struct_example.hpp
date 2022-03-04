
#ifndef STRUCT_EXAMPLE_H
#define STRUCT_EXAMPLE_H
#include <string>
#include <iostream>
using namespace std;

struct DataGeneratorParam {
	 int num;
	 int bar;
	 std::string name;
	 std::string city;
	 DataGeneratorParam() : bar(6){} // a constructor
	 int getBar() {
		 return bar;
	 }
	 //void DataGeneratorParam (int cnt, string name);
	//  void Greet(std::string name);

};

// DataGeneratorParam::DataGeneratorParam(int num, string name, string city)
// : num(num),
// name(name),
// city(city),
// void Greet(string name) {
// 	cout << "Welcome " << name << endl;
// }

class hello {
	public:
		void print();
};

void hello::print() {
	cout << "hello world" << endl;
}

#endif