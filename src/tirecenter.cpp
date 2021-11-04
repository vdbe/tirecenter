#include "tirecenter.hpp"

#include <string>
#include <vector>

#include "article.hpp"
#include "customer.hpp"

std::string TireCenter::getName(void)
{
	return this->name;
}

void TireCenter::setName(std::string name)
{
	this->name = name;
}

std::string TireCenter::getAddress(void)
{
	return this->address;
}

void TireCenter::setAddress(std::string address)
{
	this->address = address;
}

std::vector<Article> TireCenter::getArticles()
{
	// TODO:
	return {};
}

void TireCenter::setArticles(std::vector<Article>)
{
	// TODO:
}

void TireCenter::addArticle(Article article)
{
	// TODO:
}

std::vector<Customer> TireCenter::getCustomers()
{
	// TODO:
	return {};
}

void TireCenter::setCustomers(std::vector<Customer>)
{
	// TODO:
}

void TireCenter::addCustomer(Customer customer)
{
	// TODO:
}
