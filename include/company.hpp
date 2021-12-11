#pragma once
#include <string>

#include "customer.hpp"

class Company : public Customer {
private:
  std::string vat;
  int64_t volumeDiscount;

public:
  Company();
  Company(std::string, std::string, char, std::string, int64_t);
  ~Company();

  std::string getVAT(void) const;
  void setVAT(std::string);

  int64_t getVolumeDiscount(void) const;
  void setVolumeDiscount(int64_t);

  void show(void) const;
  Customer *clone(void) const;
};
