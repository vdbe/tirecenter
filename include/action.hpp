#pragma once

#include <vector>
class Article;
class Invoice;
class Customer;

namespace action {

enum class UserType { employee = 0, owner, _LENGTH };
[[maybe_unused]] static const char *USERTYPE_STRING[] = {"owner", "employee"};
static_assert(sizeof(USERTYPE_STRING) / sizeof(USERTYPE_STRING[0]) ==
                  static_cast<size_t>(UserType::_LENGTH),
              "Amount of UserType not equal to descriptions");
inline const char *userTypeToCharArray(UserType);

enum class Action {
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
  _LENGTH,
};
[[maybe_unused]] static const char *ACTION_STRING[] = {
    "change article",  "check invoices",
    "place order",     "change customer",
    "add customer",    "update stock",
    "add article",     "delete article",
    "delete customer", "exit"};
static_assert(sizeof(ACTION_STRING) / sizeof(ACTION_STRING[0]) ==
                  static_cast<size_t>(Action::_LENGTH),
              "Amount of actions not equal to descriptions");
inline const char *actionToCharArray(Action);

UserType getUserType(void);
Action chooseAction(UserType);
void runAction(Action, std::vector<Article *> &, std::vector<Customer *> &,
               std::vector<Invoice *> &);

// Actions
void actionChangeArticle(std::vector<Article *> &);
void actionPlaceOrder(std::vector<Article *> &, std::vector<Customer *> &,
                      std::vector<Invoice *> &);
void actionCheckInvoices(std::vector<Invoice *> &);
void actionChangeCustomer(std::vector<Customer *> &);
void actionAddCustomer(std::vector<Customer *> &);
void actionUpdateStock(std::vector<Article *> &);
void actionAddArticle(std::vector<Article *> &);
void actionDeleteArticle(std::vector<Article *> &);
void actionDeleteCustomer(std::vector<Customer *> &);

} // namespace action
