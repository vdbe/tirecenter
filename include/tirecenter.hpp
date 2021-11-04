#pragma once

#include <string>
#include <vector>

#include "article.hpp"
#include "customer.hpp"

class TireCenter
{
	private:
		std::string name;
		std::string address;
		std::vector<Article> articles;
		std::vector<Customer> customers;

	public:
		std::string getName(void);
		void setName(std::string);

		std::string getAddress(void);
		void setAddress(std::string);

		std::vector<Article> getArticles(void);
		void setArticles(std::vector<Article>);
		void addArticle(Article);

		std::vector<Customer> getCustomers(void);
		void setCustomers(std::vector<Customer>);
		void addCustomer(Customer);
};
