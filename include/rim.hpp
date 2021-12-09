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

  bool getAluminium(void);
  void setAluminium(bool);

  std::string getColor(void);
  void setColor(std::string);

  int64_t getWidth(void);
  void setWidth(int64_t);

  void show(void);
  void showSummary(void);
  Article *clone(void) const;
};
