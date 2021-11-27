#pragma once
#include <string>

#include "customer.hpp"

class Company : public Customer {
private:
  std::string vat;
  int volumeDiscount;

public:
  Company();
  Company(std::string, std::string, char, std::string, int);
  ~Company();

  std::string getVAT(void);
  void setVAT(std::string);

  int getVolumeDiscount(void);
  void setVolumeDiscount(int);

  void show(void);
};
