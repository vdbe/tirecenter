#pragma once
#include <vector>

#include "article.hpp"

class Tire : public Article {
private:
  int64_t width;
  int64_t height;
  std::string speedIndex;
  char season;

public:
  Tire();
  Tire(std::string, std::string, int64_t, int64_t, float, char, int64_t,
       int64_t, std::string, char);
  ~Tire();

  int64_t getWidth(void) const;
  void setWidth(int64_t);

  int64_t getHeight(void) const;
  void setHeight(int64_t);

  std::string getSpeedIndex(void) const;
  void setSpeedIndex(std::string);

  char getSeason(void) const;
  void setSeason(char);

  void show(void) const;
  void showSummary(void) const;
  Article *clone(void) const;
};
