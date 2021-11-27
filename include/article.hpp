#pragma once
#include <string>
#include <vector>

class Article {
protected:
  std::string name;
  std::string manufacturer;
  int stock;
  int diameter;
  float price;
  char type;

public:
  Article();
  Article(std::string, std::string, int, int, float, char);
  ~Article();

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

  virtual void show(void);
};
