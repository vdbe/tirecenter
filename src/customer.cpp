#include <iostream>

#include "customer.hpp"

Customer::Customer() {}
Customer::Customer(std::string name, std::string address, char type)
    : name(name), address(address), type(type) {}

Customer::~Customer() {
#ifdef PRINT_DESTRUCTORS
  std::cout << "Customer::~Customer()" << std::endl;
#endif
}

std::string Customer::getName(void) const { return this->name; }

void Customer::setName(std::string name) { this->name = name; }

std::string Customer::getAddress(void) const { return this->address; }

void Customer::setAddress(std::string address) { this->address = address; }

char Customer::getType(void) const { return this->type; }

void Customer::setType(char type) { this->type = type; }

void Customer::show(void) const {
  std::cout << "=== Customer ===" << std::endl
            << "\tName: " << this->name << std::endl
            << "\tAddress: " << this->address << std::endl
            << "\tType: " << this->type << std::endl;
}

Customer *Customer::clone(void) const { return new Customer(*this); }
