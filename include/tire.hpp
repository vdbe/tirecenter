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

  int64_t getWidth(void);
  void setWidth(int64_t);

  int64_t getHeight(void);
  void setHeight(int64_t);

  std::string getSpeedIndex(void);
  void setSpeedIndex(std::string);

  char getSeason(void);
  void setSeason(char);

  void show(void);
  void save(std::ofstream &);
  void load(std::ifstream &);
};
