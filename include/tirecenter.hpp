#pragma once

#include <string>
#include <variant>
#include <vector>

// TODO: Figure out why this does not work
// class Article;
// class Customer;
// class Invoice;

#include "article.hpp"
#include "customer.hpp"
#include "invoice.hpp"

class TireCenter {
private:
  std::string name;
  std::string address;
  std::vector<Article> articles;
  std::vector<Customer> customers;
  std::vector<Invoice> invoices;

public:
  std::string getName(void);
  void setName(std::string);

  std::string getAddress(void);
  void setAddress(std::string);

  std::vector<Article> getArticles(void);
  std::vector<Article> &getArticlesRef(void);
  void setArticles(std::vector<Article>);
  void addArticle(Article);

  std::vector<Customer> getCustomers(void);
  std::vector<Customer> &getCustomersRef(void);
  void setCustomers(std::vector<Customer>);
  void addCustomer(Customer);

  std::vector<Invoice> getInvoices(void);
  std::vector<Invoice> &getInvoicesRef(void);
  void setInvoices(std::vector<Invoice>);
  void addInvoice(Invoice);
};
