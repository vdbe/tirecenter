#include <vector>

#include "article.hpp"
#include "customer.hpp"
#include "invoice.hpp"

Customer Invoice::getCustomer(void)
{
	return this->customer;
}

void Invoice::setCustomer(Customer)
{
	this->customer = customer;
}

void Invoice::setArticles(std::vector<Article>)
{
	// TODO:
}

std::vector<Article> Invoice::getArticles(void)
{
	// TODO:
	return  {};
}

float Invoice::getPrice(void)
{
	return this->price;
}

void Invoice::setPrice(float price)
{
	this->price = price;
}

float Invoice::calculatePrice()
{
	// TODO: Find out what this function is supposed to do
	return this->price;
}

int Invoice::getDiscount(void)
{
	return this->discount;
}

void Invoice::setDiscount(int discount)
{
	this->discount = discount;
}

float Invoice::calculateDiscount()
{
	// TODO: Find out what this function is supposed to do
	return (float)this->discount;
}
