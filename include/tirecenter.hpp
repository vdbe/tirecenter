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
  std::vector<Article *> articles;
  std::vector<Customer *> customers;
  std::vector<Invoice *> invoices;

public:
  TireCenter();
  TireCenter(std::string, std::string, std::vector<Article *>,
             std::vector<Customer *>, std::vector<Invoice *>);

  ~TireCenter();

  std::string getName(void) const;
  void setName(std::string);

  std::string getAddress(void) const;
  void setAddress(std::string);

  std::vector<Article *> getArticles(void) const;
  std::vector<Article *> &getArticlesRef(void);
  void setArticles(std::vector<Article *>);
  void addArticle(Article *);

  std::vector<Customer *> getCustomers(void) const;
  std::vector<Customer *> &getCustomersRef(void);
  void setCustomers(std::vector<Customer *>);
  void addCustomer(Customer *);

  std::vector<Invoice *> getInvoices(void) const;
  std::vector<Invoice *> &getInvoicesRef(void);
  void setInvoices(std::vector<Invoice *>);
  void addInvoice(Invoice *);
};
