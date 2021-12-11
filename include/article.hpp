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

  std::string getName(void) const;
  void setName(std::string);

  std::string getManufacturer(void) const;
  void setManufacturer(std::string);

  int64_t getStock(void) const;
  void setStock(int64_t);

  int64_t getDiameter(void) const;
  void setDiameter(int64_t);

  float getPrice(void) const;
  void setPrice(float);

  char getType(void) const;
  void setType(char);

  virtual void show(void) const = 0;
  virtual void showSummary(void) const = 0;
  virtual Article *clone(void) const = 0;
};
