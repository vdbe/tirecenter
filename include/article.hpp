#pragma once
#include <fstream>
#include <string>
#include <vector>

class Article {
protected:
  std::string name;
  std::string manufacturer;
  int64_t stock;
  int64_t diameter;
  float price;
  char type;

public:
  Article();
  Article(std::string, std::string, int64_t, int64_t, float, char);
  virtual ~Article();

  std::string getName(void);
  void setName(std::string);

  std::string getManufacturer(void);
  void setManufacturer(std::string);

  int64_t getStock(void);
  void setStock(int64_t);

  int64_t getDiameter(void);
  void setDiameter(int64_t);

  float getPrice(void);
  void setPrice(float);

  char getType(void);
  void setType(char);

  virtual void show(void);
};
