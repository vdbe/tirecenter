#pragma once
#include <vector>

#include "article.hpp"

class Tire : public Article {
private:
  int width;
  int height;
  std::string speedIndex;
  char season;

public:
  Tire();
  Tire(std::string, std::string, int, int, float, char, int, int, std::string,
       char);
  ~Tire();

  int getWidth(void);
  void setWidth(int);

  int getHeight(void);
  void setHeight(int);

  std::string getSpeedIndex(void);
  void setSpeedIndex(std::string);

  char getSeason(void);
  void setSeason(char);

  void show(void);
};
