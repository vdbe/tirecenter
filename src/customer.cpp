#include "customer.hpp"

std::string Customer::getName(void)
{
	return this->name;
}

void Customer::setName(std::string name)
{
	this->name = name;
}

std::string Customer::getAddress(void)
{
	return this->address;
}

void Customer::setAddress(std::string address)
{
	this->address = address;
}

char Customer::getType(void)
{
	return this->type;
}

void Customer::setType(char type)
{
	this->type = type;
}
