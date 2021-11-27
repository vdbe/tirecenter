#pragma once
#include <string>
#include <vector>

class Article {
private:
  std::string name;
  std::string manufacturer;
  int stock;
  int diameter;
  float price;
  char type;

public:
  std::string getName(void);
  void setName(std::string);

  std::string getManufacturer(void);
  void setManufacturer(std::string);

  int getStock(void);
  void setStock(int);

  int getDiameter(void);
  void setDiameter(int);

  float getPrice(void);
  void setPrice(float);

  char getType(void);
  void setType(char);

  void show(void);
};
