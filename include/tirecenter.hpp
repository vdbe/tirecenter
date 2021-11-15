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

enum UserType {
  owner,
  employee,
};
[[maybe_unused]] static const char *USERTYPE_STRING[] = {"owner", "employee"};

enum Action {
  changeArticle,
  checkInvoices,
  placeOrder,
  changeCustomer,
  addCustomer,
  updateStock,
  addArticle,
  deleteArticle,
  deleteCustomer,
  exitMenu,
};
[[maybe_unused]] static const char *ACTION_STRING[] = {
    "change article",  "check invoices",
    "place order",     "change customer",
    "add customer",    "update stock",
    "add article",     "delete article",
    "delete customer", "exit"};

class TireCenter {
private:
  std::string name;
  std::string address;
  std::vector<Article> articles;
  std::vector<Customer> customers;
  std::vector<Invoice> invoices;

  void actionChangeArticle(void);
  void actionPlaceOrder(void);
  void actionCheckInvoices(void);
  void actionChangeCustomer(void);
  void actionAddCustomer(void);
  void actionUpdateStock(void);
  void actionAddArticle(void);
  void actionDeleteArticle(void);
  void actionDeleteCustomer(void);

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

  std::vector<Invoice> getInvoices(void);
  void setInvoices(std::vector<Invoice>);
  void addInvoice(Invoice);

  static UserType getUserType(void);
  static Action chooseAction(UserType);
  void runAction(Action);
};
