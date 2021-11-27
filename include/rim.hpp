#pragma once
#include <vector>

#include "article.hpp"

class Rim : public Article {
private:
  bool aluminium;
  std::string color;
  int width;

public:
  Rim(std::string, std::string, int, int, float, char, bool, std::string, int);
  Rim();
  ~Rim();
  bool getAluminium(void);
  void setAluminium(bool);

  std::string getColor(void);
  void setColor(std::string);

  int getWidth(void);
  void setWidth(int);

  void show(void);
};
