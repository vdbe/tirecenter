#pragma once
#include <vector>

#include "article.hpp"

class Rim : public Article {
private:
  bool aluminium;
  std::string color;
  int64_t width;

public:
  Rim(std::string, std::string, int64_t, int64_t, float, char, bool,
      std::string, int64_t);
  Rim();
  ~Rim();

  bool getAluminium(void) const;
  void setAluminium(bool);

  std::string getColor(void) const;
  void setColor(std::string);

  int64_t getWidth(void) const;
  void setWidth(int64_t);

  void show(void) const;
  void showSummary(void) const;
  Article *clone(void) const;
};
