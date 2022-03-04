
#include <iostream>
#include "struct_example.hpp"

int main() {
//   DataGeneratorParam::DataGeneratorParam(int num) {
// 	  for(int i = 0; i < num; i++) {
// 	  cout << ""The data genearated is "" << i <<endl;
// }
// DataGeneratorParam::DataGeneratorParam(8);
	std::string name = "jack";
	std::string city = "Beijing";
	DataGeneratorParam data;
	int x = data.getBar();
	std::cout << "The return bar is " << x << std::endl;
	hello hi;
	hi.print();
	return 0;
}
