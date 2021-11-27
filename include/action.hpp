#pragma once

#include <vector>
class Article;
class Invoice;
class Customer;

enum UserType { employee = 0, owner, _LENGTH_USERTYPE };
[[maybe_unused]] static const char *USERTYPE_STRING[] = {"owner", "employee"};
static_assert(sizeof(USERTYPE_STRING) / sizeof(USERTYPE_STRING[0]) ==
                  (unsigned int)UserType::_LENGTH_USERTYPE,
              "Amount of UserType not equal to descriptions");
inline const char *userTypeToCharArray(UserType);

enum Action {
  changeArticle = 0,
  checkInvoices,
  placeOrder,
  changeCustomer,
  addCustomer,
  updateStock,
  addArticle,
  deleteArticle,
  deleteCustomer,
  exitMenu,
  _LENGTH_ACTION,
};
[[maybe_unused]] static const char *ACTION_STRING[] = {
    "change article",  "check invoices",
    "place order",     "change customer",
    "add customer",    "update stock",
    "add article",     "delete article",
    "delete customer", "exit"};
static_assert(sizeof(ACTION_STRING) / sizeof(ACTION_STRING[0]) ==
                  (unsigned int)Action::_LENGTH_ACTION,
              "Amount of actions not equal to descriptions");
inline const char *actionToCharArray(Action);

UserType getUserType(void);
Action chooseAction(UserType);
void runAction(Action, std::vector<Article> &, std::vector<Customer> &,
               std::vector<Invoice> &);

// Actions
void actionChangeArticle(std::vector<Article> &);
void actionPlaceOrder(std::vector<Article> &, std::vector<Customer> &,
                      std::vector<Invoice> &);
void actionCheckInvoices(std::vector<Invoice> &);
void actionChangeCustomer(std::vector<Customer> &);
void actionAddCustomer(std::vector<Customer> &);
void actionUpdateStock(std::vector<Article> &);
void actionAddArticle(std::vector<Article> &);
void actionDeleteArticle(std::vector<Article> &);
void actionDeleteCustomer(std::vector<Customer> &);
