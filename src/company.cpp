#include "company.hpp"

#include <iostream>

#include "customer.hpp"

Company::Company(){};
Company::Company(std::string name, std::string address, char type,
                 std::string vat, int volumeDiscount)
    : Customer(name, address, type), vat(vat), volumeDiscount(volumeDiscount) {}

Company::~Company(){};

std::string Company::getVAT(void) { return this->vat; }

void Company::setVAT(std::string vat) { this->vat = vat; }

int Company::getVolumeDiscount(void) { return this->volumeDiscount; }

void Company::setVolumeDiscount(int volumeDiscount) {
  this->volumeDiscount = volumeDiscount;
}

void Company::show(void) {
  std::cout << "=== Company ===" << std::endl
            << "\tName: " << this->name << std::endl
            << "\tAddress: " << this->address << std::endl
            << "\tVAT: " << this->vat << std::endl
            << "\tVolume Discount: " << this->volumeDiscount << std::endl
            << "\tType: " << this->type << std::endl;
}
