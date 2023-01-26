#include <iostream>
#include <memory>

enum gender { male = 0, female = 1 };
class People {
 public:
  People(std::string name, int age, gender gender)
      : _name(name), _age(age), _gender(gender) {}
  ~People() {}

  void Age() { std::cout << _name << "'s age is " << _age << std::endl; }

 private:
  std::string _name;
  int _age;
  gender _gender;
};

int main() {
  People Jack("Jack", 10, male);
  Jack.Age();

  // C++ 11
  People *tom_ptr = new People("Tom", 12, male);
  std::shared_ptr<People> tom_sp1(new People("Tom", 13, male));
  std::shared_ptr<People> tom_sp2(tom_ptr);
  std::shared_ptr<People> tom_sp3(tom_sp2);

  std::cout << "tom sp1 use_count " << tom_sp1.use_count() << std::endl;
  std::cout << "tom sp2 use_count " << tom_sp2.use_count() << std::endl;
  std::cout << "tom sp3 use_count " << tom_sp3.use_count() << std::endl;

  std::cout << "tom_sp1 original pointer is " << tom_sp1.get() << std::endl;
  std::cout << "tom_sp2 original pointer is " << tom_sp2.get() << std::endl;
  std::cout << "tom_sp3 original pointer is " << tom_sp3.get() << std::endl;

  tom_sp3.reset();

  std::cout << "tom sp1 use_count " << tom_sp1.use_count() << std::endl;
  std::cout << "tom sp2 use_count " << tom_sp2.use_count() << std::endl;
  std::cout << "tom sp3 use_count " << tom_sp3.use_count() << std::endl;

  // C++ 14 create the object and return its shared_pointer
  auto tom_sp = std::make_shared<People>("Tom", 11, male);
  tom_sp->Age();

  auto peny_sp = std::make_unique<People>("Peny", 12, female);
  peny_sp->Age();

  std::unique_ptr<People> new_peny_sp = std::move(peny_sp);

  if (peny_sp) peny_sp->Age();
  new_peny_sp->Age();

  return 0;
}