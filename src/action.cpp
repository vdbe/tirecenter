#include "action.hpp"

#include <vector>

#include "article.hpp"
#include "customer.hpp"
#include "invoice.hpp"
#include "lib.hpp"

inline const char *userTypeToCharArray(UserType userType) {
  return USERTYPE_STRING[userType];
}

inline const char *actionToCharArray(Action action) {
  return ACTION_STRING[action];
}

/* static functions */
Action chooseAction(UserType user) {
  Action action;
  int len = 6;
  char **options = NULL;

  // Add options for owner
  if (user == UserType::owner) {
    len += 3;
  }

  // Allocate memory for option pointers
  options = (char **)malloc((len + 1) * sizeof(char **));
  // options = (char **)calloc(len, sizeof(char **));
  if (options == NULL)
    exit(1);

  for (int ii = 0; ii < len; ii++) {
    options[ii] = (char *)ACTION_STRING[ii];
  }
  options[len] = (char *)actionToCharArray(Action::exitMenu);

  action = (Action)choose(options, len + 1, 8);

  free(options);
  return action;
}

UserType getUserType(void) {
  UserType user;
  char *options[2];
  size_t choice;

  options[0] = (char *)userTypeToCharArray(UserType::employee);
  options[1] = (char *)userTypeToCharArray(UserType::owner);
  choice = choose((char **)options, 2, 8);

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

  std::string line;

  SearchResult<Article> searchResult = search(articles, &Article::getName);

  std::cout << "Leave blank if old value is correct" << std::endl;

  std::cout << "Name: ";
  std::cout << searchResult.item.getName() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "") {
    searchResult.item.setName(line);
  }

  std::cout << "Manufacturer: ";
  std::cout << searchResult.item.getManufacturer() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "") {
    searchResult.item.setManufacturer(line);
  }

  std::cout << "Diameter: ";
  std::cout << searchResult.item.getDiameter() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "" && stringIsInt(line)) {
    searchResult.item.setDiameter(std::stoi(line));
  }

  std::cout << "Type: ";
  std::cout << searchResult.item.getType() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "" && stringIsInt(line)) {
    searchResult.item.setType(line[0]);
  }

  std::cout << "Stock: ";
  std::cout << searchResult.item.getStock() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "" && stringIsInt(line)) {
    searchResult.item.setStock(std::stoi(line));
  }

  std::cout << "Price: ";
  std::cout << searchResult.item.getPrice() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "" && stringIsFloat(line)) {
    searchResult.item.setStock(std::stof(line));
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
  SearchResult<Customer> customerSearch = search(customers, &Customer::getName);

  invoice.setCustomer(customerSearch.item);

  do {
    int stock;
    int amount = 0;

    SearchResult<Article> articleSearch = search(articles, &Article::getName);

    Article local_article = articleSearch.item;

    // Update stock
    std::cout << "Amount: ";
    std::cin >> amount;
    local_article.setStock(amount);

    // Check if their is enough stock
    stock = articleSearch.item.getStock();
    if (amount <= stock) {
      articleSearch.item.setStock(stock - amount);
      order_articles.push_back(local_article);
    } else {
      std::cout << "Cant place order not enough stock, " << std::endl
                << "current stock: " << stock << std::endl;
    }

    std::cout << "Add another article? [y/n]: ";
    std::cin >> c;
    cleanStdin();
  } while (c == 'y');

  invoice.setArticles(order_articles);

  // TODO : Check if both are needed invoice.calculatePrice();
  invoice.calculateDiscount();

  invoices.push_back(invoice);
}

void actionChangeCustomer(std::vector<Customer> &customers) {
  std::string line;

  SearchResult<Customer> searchResult = search(customers, &Customer::getName);

  std::cout << "Leave blank if old value is correct" << std::endl;

  std::cout << "Name: ";
  std::cout << searchResult.item.getName() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "") {
    searchResult.item.setName(line);
  }

  std::cout << "Address: ";
  std::cout << searchResult.item.getAddress() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "") {
    searchResult.item.setAddress(line);
  }

  std::cout << "Type: ";
  std::cout << searchResult.item.getType() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "") {
    searchResult.item.setType(line[0]);
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

  std::string line;

  SearchResult<Article> searchResult = search(articles, &Article::getName);

  std::cout << "Leave blank if old value is correct" << std::endl;

  std::cout << "Stock: ";
  std::cout << searchResult.item.getStock() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "" && stringIsInt(line)) {
    searchResult.item.setStock(std::stoi(line));
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
  SearchResult<Article> searchResult = search(articles, &Article::getName);
  deleteFromVec(articles, searchResult, &Article::show);
}

void actionDeleteCustomer(std::vector<Customer> &customers) {
  SearchResult<Customer> searchResult = search(customers, &Customer::getName);
  deleteFromVec(customers, searchResult, &Customer::show);
}
