#pragma once
#include <string>

class Customer {
protected:
  std::string name;
  std::string address;
  char type;

public:
  Customer();
  Customer(std::string, std::string, char);
  ~Customer();
  std::string getName(void);
  void setName(std::string);

  std::string getAddress(void);
  void setAddress(std::string);

  char getType(void);
  void setType(char);

  virtual void show(void);
};
