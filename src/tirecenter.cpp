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

void TireCenter::setArticles(std::vector<Article> articles) {
  this->articles = articles;
}

void TireCenter::addArticle(Article article) {
  this->articles.push_back(article);
}

std::vector<Customer> TireCenter::getCustomers() { return this->customers; }

void TireCenter::setCustomers(std::vector<Customer> customers) {
  this->customers = customers;
}

void TireCenter::addCustomer(Customer customer) {
  this->customers.push_back(customer);
}

std::vector<Invoice> TireCenter::getInvoices() { return this->invoices; }

void TireCenter::setInvoices(std::vector<Invoice> invoices) {
  this->invoices = invoices;
}

void TireCenter::addInvoice(Invoice invoice) {
  this->invoices.push_back(invoice);
}

/* static functions */
Action TireCenter::chooseAction(UserType user) {
  Action action;
  int len = 6;

  // Add options for owner
  if (user == UserType::owner) {
    len += 3;
  }

  std::vector<std::string> options(len + 1);
  for (int ii = 0; ii < len; ii++) {
    options[ii] = ACTION_STRING[ii];
  }
  options[len] = ACTION_STRING[Action::exitMenu];

  Menu menu(options);
  action = (Action)menu.run();

  return action;
}

UserType TireCenter::getUserType(void) {
  UserType user;

  std::vector<std::string> options(2);
  options[0] = USERTYPE_STRING[0];
  options[1] = USERTYPE_STRING[1];

  Menu menu(options);
  int choice = menu.run();
  switch (choice) {
  case 0:
    user = UserType::owner;
    break;
  case 1:
    user = UserType::employee;
    break;
  default:
    // TODO: Error handling should never reach hear
    user = UserType::employee;
    std::cerr << "Invalid user type: " << choice << std::endl;
  }

  return user;
}

/* normal public functions */
void TireCenter::runAction(Action action) {
  switch (action) {
  case Action::changeArticle:
    this->actionChangeArticle();
    break;
  case Action::checkInvoices:
    this->actionCheckInvoices();
    break;
  case Action::placeOrder:
    this->actionPlaceOrder();
    break;
  case Action::changeCustomer:
    this->actionChangeCustomer();
    break;
  case Action::addCustomer:
    this->actionAddCustomer();
    break;
  case Action::updateStock:
    this->actionUpdateStock();
    break;
  case Action::addArticle:
    this->actionAddArticle();
    break;
  case Action::deleteArticle:
    this->actionDeleteArticle();
    break;
  case Action::deleteCustomer:
    this->actionDeleteCustomer();
    break;
  case Action::exitMenu:
    // Do nothing
    return;
    break;
  default:
    // TODO: Error handling
    std::cerr << "Invalid action type: " << action << std::endl;
    break;
  }
}

/*
 * Private Function
 */
/* Actions */
void TireCenter::actionChangeArticle(void) {
  Article *p_article;
  SearchResult<Article> searchResult;

  std::string line;

  searchResult = search(&this->articles, &Article::getName);
  p_article = searchResult.ptr;

  std::cout << "Leave blank if old value is correct" << std::endl;

  std::cout << "Name: ";
  std::cout << p_article->getName() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "") {
    p_article->setName(line);
  }

  std::cout << "Manufacturer: ";
  std::cout << p_article->getManufacturer() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "") {
    p_article->setManufacturer(line);
  }

  std::cout << "Diameter: ";
  std::cout << p_article->getDiameter() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "" && stringIsInt(line)) {
    p_article->setDiameter(std::stoi(line));
  }

  std::cout << "Type: ";
  std::cout << p_article->getType() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "" && stringIsInt(line)) {
    p_article->setType(line[0]);
  }

  std::cout << "Stock: ";
  std::cout << p_article->getStock() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "" && stringIsInt(line)) {
    p_article->setStock(std::stoi(line));
  }

  std::cout << "Price: ";
  std::cout << p_article->getPrice() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "" && stringIsFloat(line)) {
    p_article->setStock(std::stof(line));
  }
}

void TireCenter::actionCheckInvoices(void) {
  // TODO:
}

void TireCenter::actionPlaceOrder(void) {
  char c;
  Invoice invoice;
  std::vector<Article> articles;
  SearchResult<Customer> customerSearch;
  SearchResult<Article> articleSearch;

  customerSearch = search(&this->customers, &Customer::getName);
  invoice.setCustomer(*customerSearch.ptr);

  do {
    int stock;
    int amount = 0;

    articleSearch = search(&this->articles, &Article::getName);

    Article article = *articleSearch.ptr;

    // Update stock
    std::cout << "Amount: ";
    std::cin >> amount;
    article.setStock(amount);

    // Check if their is enough stock
    stock = articleSearch.ptr->getStock();
    if (amount <= stock) {
      articleSearch.ptr->setStock(stock - amount);
      articles.push_back(*articleSearch.ptr);
    } else {
      std::cout << "Cant place order not enough stock, " << std::endl
                << "current stock: " << stock << std::endl;
    }

    std::cout << "Add another article? [y/n]: ";
    std::cin >> c;
    cleanStdin();
  } while (c == 'y');

  // TODO: Check if both are needed
  invoice.calculatePrice();
  invoice.calculateDiscount();

  this->invoices.push_back(invoice);
}

void TireCenter::actionChangeCustomer(void) {
  Customer *p_customer;
  SearchResult<Customer> searchResult;

  std::string line;

  searchResult = search(&this->customers, &Customer::getName);
  p_customer = searchResult.ptr;

  std::cout << "Leave blank if old value is correct" << std::endl;

  std::cout << "Name: ";
  std::cout << p_customer->getName() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "") {
    p_customer->setName(line);
  }

  std::cout << "Address: ";
  std::cout << p_customer->getAddress() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "") {
    p_customer->setAddress(line);
  }

  std::cout << "Type: ";
  std::cout << p_customer->getType() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "") {
    p_customer->setType(line[0]);
  }
}

void TireCenter::actionAddCustomer(void) {
  Customer customer;

  std::string line;
  char c;

  std::cout << "Name: ";
  std::getline(std::cin, line);
  customer.setName(line);

  std::cout << "Address: ";
  std::getline(std::cin, line);
  customer.setAddress(line);

  std::cout << "Type: ";
  std::cin >> c;
  customer.setType(c);

  this->customers.push_back(customer);
}

void TireCenter::actionUpdateStock(void) {
  Article *p_article;
  SearchResult<Article> searchResult;

  std::string line;

  searchResult = search(&this->articles, &Article::getName);
  p_article = searchResult.ptr;

  std::cout << "Leave blank if old value is correct" << std::endl;

  std::cout << "Stock: ";
  std::cout << p_article->getStock() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "" && stringIsInt(line)) {
    p_article->setStock(std::stoi(line));
  }
}

void TireCenter::actionAddArticle(void) {
  Article article;

  std::string line;
  int integer;
  char c;
  float f;

  std::cout << "Name: ";
  std::getline(std::cin, line);
  article.setName(line);

  std::cout << "Manufacturer: ";
  std::getline(std::cin, line);
  article.setManufacturer(line);

  std::cout << "Diameter: ";
  std::cin >> integer;
  article.setDiameter(integer);

  std::cout << "Type: ";
  std::cin >> c;
  article.setType(c);

  std::cout << "Stock: ";
  std::cin >> integer;
  article.setStock(integer);

  std::cout << "Price: ";
  std::cin >> f;
  article.setPrice(f);

  cleanStdin();

  this->addArticle(article);
}

void TireCenter::actionDeleteArticle(void) {
  SearchResult<Article> searchResult;

  searchResult = search(&this->articles, &Article::getName);
  deleteFromVec(&this->articles, searchResult, &Article::show);
}

void TireCenter::actionDeleteCustomer(void) {
  SearchResult<Customer> searchResult;

  searchResult = search(&this->customers, &Customer::getName);
  deleteFromVec(&this->customers, searchResult, &Customer::show);
}
