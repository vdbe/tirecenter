#include "action.hpp"

#include <vector>

#include "article.hpp"
#include "customer.hpp"
#include "invoice.hpp"
#include "lib.hpp"

/* static functions */
Action chooseAction(UserType user) {
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

UserType getUserType(void) {
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
void runAction(Action action, std::vector<Article> &articles,
               std::vector<Customer> &customers,
               std::vector<Invoice> &invoices) {
  switch (action) {
  case Action::changeArticle:
    actionChangeArticle(articles);
    break;
  case Action::checkInvoices:
    actionCheckInvoices(invoices);
    break;
  case Action::placeOrder:
    actionPlaceOrder(articles, customers, invoices);
    break;
  case Action::changeCustomer:
    actionChangeCustomer(customers);
    break;
  case Action::addCustomer:
    actionAddCustomer(customers);
    break;
  case Action::updateStock:
    actionUpdateStock(articles);
    break;
  case Action::addArticle:
    actionAddArticle(articles);
    break;
  case Action::deleteArticle:
    actionDeleteArticle(articles);
    break;
  case Action::deleteCustomer:
    actionDeleteCustomer(customers);
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

/* Actions */
void actionChangeArticle(std::vector<Article> &articles) {
  Article *p_article;
  SearchResult<Article> searchResult;

  std::string line;

  searchResult = search(&articles, &Article::getName);
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

void actionCheckInvoices(std::vector<Invoice> &invoices) {
  // TODO:
}

void actionPlaceOrder(std::vector<Article> &articles,
                      std::vector<Customer> &customers,
                      std::vector<Invoice> &invoices) {
  char c;
  Invoice invoice;
  std::vector<Article> order_articles;
  SearchResult<Customer> customerSearch;
  SearchResult<Article> articleSearch;

  customerSearch = search(&customers, &Customer::getName);
  invoice.setCustomer(*customerSearch.ptr);

  do {
    int stock;
    int amount = 0;

    articleSearch = search(&articles, &Article::getName);

    Article article = *articleSearch.ptr;

    // Update stock
    std::cout << "Amount: ";
    std::cin >> amount;
    article.setStock(amount);

    // Check if their is enough stock
    stock = articleSearch.ptr->getStock();
    if (amount <= stock) {
      articleSearch.ptr->setStock(stock - amount);
      order_articles.push_back(*articleSearch.ptr);
    } else {
      std::cout << "Cant place order not enough stock, " << std::endl
                << "current stock: " << stock << std::endl;
    }

    std::cout << "Add another article? [y/n]: ";
    std::cin >> c;
    cleanStdin();
  } while (c == 'y');
  invoice.setArticles(order_articles);

  // TODO: Check if both are needed
  invoice.calculatePrice();
  invoice.calculateDiscount();

  invoices.push_back(invoice);
}

void actionChangeCustomer(std::vector<Customer> &customers) {
  Customer *p_customer;
  SearchResult<Customer> searchResult;

  std::string line;

  searchResult = search(&customers, &Customer::getName);
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

void actionAddCustomer(std::vector<Customer> &customers) {
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

  customers.push_back(customer);
}

void actionUpdateStock(std::vector<Article> &articles) {
  Article *p_article;
  SearchResult<Article> searchResult;

  std::string line;

  searchResult = search(&articles, &Article::getName);
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

void actionAddArticle(std::vector<Article> &articles) {
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

  articles.push_back(article);
}

void actionDeleteArticle(std::vector<Article> &articles) {
  SearchResult<Article> searchResult;

  searchResult = search(&articles, &Article::getName);
  deleteFromVec(&articles, searchResult, &Article::show);
}

void actionDeleteCustomer(std::vector<Customer> &customers) {
  SearchResult<Customer> searchResult;

  searchResult = search(&customers, &Customer::getName);
  deleteFromVec(&customers, searchResult, &Customer::show);
}
