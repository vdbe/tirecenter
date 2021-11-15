#pragma once
#include <string>

class Company {
private:
  std::string vat;
  int volumeDiscount;

public:
  std::string getVAT(void);
  void setVAT(std::string);

  int getVolumeDiscount(void);
  void setVolumeDiscount(int);
};
