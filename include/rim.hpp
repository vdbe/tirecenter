#pragma once
#include <vector>

#include "article.hpp"

class Rim : public Article {
private:
  bool aluminium;
  std::string color;
  int width;

public:
  bool getAluminium(void);
  void setAluminium(bool);

  std::string getColor(void);
  void setColor(std::string);

  int getWidth(void);
  void setWidth(int);
};
