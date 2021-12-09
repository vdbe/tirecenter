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
  virtual ~Customer();

  std::string getName(void) const;
  void setName(std::string);

  std::string getAddress(void) const;
  void setAddress(std::string);

  char getType(void) const;
  void setType(char);

  virtual void show(void) const;
};
