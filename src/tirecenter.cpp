#include "tirecenter.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "article.hpp"
#include "customer.hpp"
#include "invoice.hpp"
#include "lib.hpp"

/*
 * Public Function
 */
/* getters and setter */
std::string TireCenter::getName(void) { return this->name; }

void TireCenter::setName(std::string name) { this->name = name; }

std::string TireCenter::getAddress(void) { return this->address; }

void TireCenter::setAddress(std::string address) { this->address = address; }

std::vector<Article> TireCenter::getArticles() { return this->articles; }

std::vector<Article> &TireCenter::getArticlesRef() { return this->articles; }

void TireCenter::setArticles(std::vector<Article> articles) {
  this->articles = articles;
}

void TireCenter::addArticle(Article article) {
  this->articles.push_back(article);
}

std::vector<Customer> TireCenter::getCustomers() { return this->customers; }

std::vector<Customer> &TireCenter::getCustomersRef() { return this->customers; }

void TireCenter::setCustomers(std::vector<Customer> customers) {
  this->customers = customers;
}

void TireCenter::addCustomer(Customer customer) {
  this->customers.push_back(customer);
}

std::vector<Invoice> TireCenter::getInvoices() { return this->invoices; }
std::vector<Invoice> &TireCenter::getInvoicesRef() { return this->invoices; }

void TireCenter::setInvoices(std::vector<Invoice> invoices) {
  this->invoices = invoices;
}

void TireCenter::addInvoice(Invoice invoice) {
  this->invoices.push_back(invoice);
}
