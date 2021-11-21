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
  int getWidth(void);
  void setWidth(int);

  int getHeight(void);
  void setHeight(int);

  std::string getSpeedIndex(void);
  void setSpeedIndex(std::string);

  char getSeason(void);
  void setSeason(char);
};
