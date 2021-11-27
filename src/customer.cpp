#include <iostream>

#include "customer.hpp"

Customer::Customer(){};
Customer::Customer(std::string name, std::string address, char type)
    : name(name), address(address), type(type) {}
Customer::~Customer(){};

std::string Customer::getName(void) { return this->name; }

void Customer::setName(std::string name) { this->name = name; }

std::string Customer::getAddress(void) { return this->address; }

void Customer::setAddress(std::string address) { this->address = address; }

char Customer::getType(void) { return this->type; }

void Customer::setType(char type) { this->type = type; }

void Customer::show(void) {
  std::cout << "=== Customer ===" << std::endl
            << "\tName: " << this->name << std::endl
            << "\tAddress: " << this->address << std::endl
            << "\tType: " << this->type << std::endl;
}
