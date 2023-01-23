#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

enum month_day {

};

enum fruit_set { apple = 0, orange, banana, mango };

struct date {
  int year;
  int month;
  int day;
  struct tm tm_;
  std::string time_str;

  time_t StringToTimeStamp() {
    sscanf(time_str.c_str(), "%d-%d-%d", &year, &month, &day);
    tm_.tm_year = year - 1900;
    tm_.tm_mon = month - 1;
    tm_.tm_mday = day;

    time_t tm_stamp = mktime(&tm_);
    return tm_stamp;
  }
};

class Fruit {
 public:
  Fruit(std::string name, std::string date_str, float price, float weight,
        date produce_date, int shelf_life)
      : _name(name),
        _price(price),
        _weight(weight),
        _produce_date(produce_date),
        _shelf_life(shelf_life) {
    time_t time_now = time(NULL);
  }
  ~Fruit() {}

  bool overtime(date purchse_date) {
    if (purchse_date.day - _produce_date.day > _shelf_life)
      return true;
    else
      return false;
  }

  Fruit& operator=(const Fruit& fruit) { _weight = _weight + fruit._weight; }

  Fruit& operator+(const Fruit& fruit) {
    if (_name == fruit._name) _weight = _weight + fruit._weight;
  }

  // virtual void SetProductionDate(date date) = 0;

 private:
  std::string _name;
  int _id;
  float _price;
  float _weight = 0;
  date _produce_date;
  int _shelf_life;
};

class SuperMarket {
 public:
  SuperMarket(const SuperMarket&) = delete;
  SuperMarket& operator=(const SuperMarket&) = delete;
  SuperMarket& operator=(const SuperMarket&& other_market) {
    if (this != &other_market) {
      _fruit_stock = std::move(other_market._fruit_stock);
      // other_market._fruit_stock = (std::nullptr_t) nullptr;
    }
    return *this;
  }
  void StockIn(Fruit fruit) {}
  void StockOut(Fruit fruit) {}

 private:
  std::shared_ptr<std::unordered_map<int, Fruit>> _fruit_stock;
};

int main() {
  std::unordered_map<int, std::string> basket;

  basket.insert(std::pair<int, std::string>(1, "apple"));
  basket.insert(std::pair<int, std::string>(2, "orange"));
  basket.insert(std::pair<int, std::string>(3, "banana"));

  if (auto it = basket.find(2); it != basket.end())
    std::cout << "Found key " << it->first << " is " << it->second << std::endl;
  else
    std::cout << "Not found." << std::endl;

  return 0;
}