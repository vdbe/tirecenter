#include "action.hpp"
#include "tcdb.hpp"

#include <vector>

#include "article.hpp"
#include "company.hpp"
#include "customer.hpp"
#include "invoice.hpp"
#include "lib.hpp"
#include "rim.hpp"
#include "tire.hpp"

namespace action {

inline const char *userTypeToCharArray(UserType userType) {
  return USERTYPE_STRING[static_cast<size_t>(userType)];
}

inline const char *actionToCharArray(Action action) {
  return ACTION_STRING[static_cast<size_t>(action)];
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
  if (options == NULL) {
    exit(1);
  }

  for (int ii = 0; ii < len; ii++) {
    options[ii] = (char *)ACTION_STRING[ii];
  }
  options[len] = (char *)actionToCharArray(Action::exitMenu);

  action = static_cast<Action>(lib::choose(options, len + 1, 8));

  free(options);
  return action;
}

UserType getUserType(void) {
  UserType user;
  char *options[2];
  size_t choice;

  options[0] = (char *)userTypeToCharArray(UserType::employee);
  options[1] = (char *)userTypeToCharArray(UserType::owner);
  choice = lib::choose((char **)options, 2, 8);

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
void runAction(Action action, std::vector<Article *> &articles,
               std::vector<Customer *> &customers,
               std::vector<Invoice *> &invoices) {
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
    std::cerr << "Invalid action type: " << static_cast<size_t>(action)
              << std::endl;
    break;
  }
}

/* Actions */
void actionChangeArticle(std::vector<Article *> &articles) {
  std::string line;

  // SearchResult<Article> searchResult = search(articles, &Article::getName);
  lib::SearchResult<Article> searchResult = lib::searchArticle(articles);

  if (searchResult.item == NULL) {
    std::cout << "No matching items" << std::endl;
    return;
  }

  std::cout << "Leave blank if old value is correct" << std::endl;

  std::cout << "Name: ";
  std::cout << searchResult.item->getName() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  lib::trim(line);
  if (line != "") {
    searchResult.item->setName(line);
  }

  std::cout << "Manufacturer: ";
  std::cout << searchResult.item->getManufacturer() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  lib::trim(line);
  if (line != "") {
    searchResult.item->setManufacturer(line);
  }

  std::cout << "Diameter: ";
  std::cout << searchResult.item->getDiameter() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  lib::trim(line);
  if (line != "" && lib::stringIsInt(line)) {
    searchResult.item->setDiameter(std::stoi(line));
  }

  // NOTE: type schould never change
  /*
  std::cout << "Type: ";
  std::cout << searchResult.item->getType() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  */
  if (line != "" && lib::stringIsInt(line)) {
    searchResult.item->setType(line[0]);
  }

  std::cout << "Stock: ";
  std::cout << searchResult.item->getStock() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "" && lib::stringIsInt(line)) {
    searchResult.item->setStock(std::stoi(line));
  }

  std::cout << "Price: ";
  std::cout << searchResult.item->getPrice() << std::endl;
  std::cout << "new: ";
  lib::trim(line);
  std::getline(std::cin, line);
  if (line != "" && lib::stringIsFloat(line)) {
    searchResult.item->setStock(std::stof(line));
  }
}

void actionCheckInvoices(std::vector<Invoice *> &invoices) {
  for (Invoice *invoice : invoices) {
    invoice->show();
  }
}

void actionPlaceOrder(std::vector<Article *> &articles,
                      std::vector<Customer *> &customers,
                      std::vector<Invoice *> &invoices) {
  Invoice *invoice = new Invoice;
  char c;
  std::vector<Article *> order_articles = invoice->getArticlesAsRef();
  // SearchResult<Customer> customerSearch = search(customers,
  // &Customer::getName);
  lib::SearchResult<Customer> customerSearch = lib::searchCustomer(customers);

  if (customerSearch.item == NULL) {
    std::cout << "No matching items" << std::endl;
    return;
  }

  invoice->setCustomer(customerSearch.item->clone());

  do {
    int stock;
    int amount = 0;

    // SearchResult<Article> articleSearch = search(articles,
    // &Article::getName);
    lib::SearchResult<Article> articleSearch = lib::searchArticle(articles);

    if (articleSearch.item == NULL) {
      std::cout << "No matching items" << std::endl;
      return;
    }

    Article *local_article = articleSearch.item->clone();
    char type = local_article->getType();

    // Update stock
    switch (type) {
    case 't':
      std::cout << "How many sets of 4 tires: ";
      break;
    case 'r':
      std::cout << "Fow many sets of 4 rims: ";
      break;
    default:
      std::cout << "Amount: ";
      break;
    }

    std::cin >> amount;
    if (type == 'r' || type == 't') {
      amount *= 4;
    }

    local_article->setStock(amount);

    // Check if their is enough stock
    stock = articleSearch.item->getStock();
    if (amount <= stock) {
      articleSearch.item->setStock(stock - amount);
      order_articles.push_back(local_article);
    } else {
      std::cout << "Cant place order not enough stock, " << std::endl
                << "current stock: " << stock << std::endl;
    }

    if (order_articles.size() > 0) {
      std::cout << "Add another article? [y/n]: ";
      std::cin >> c;
      lib::cleanStdin();
    } else {
      c = 'y';
    }
  } while (c == 'y');

  invoice->calculatePrice();
  invoice->calculateDiscount();

  invoices.push_back(invoice);
}

void actionChangeCustomer(std::vector<Customer *> &customers) {
  std::string line;

  // SearchResult<Customer> searchResult = search(customers,
  // &Customer::getName);
  lib::SearchResult<Customer> searchResult = lib::searchCustomer(customers);

  if (searchResult.item == NULL) {
    std::cout << "No matching items" << std::endl;
    return;
  }

  std::cout << "Leave blank if old value is correct" << std::endl;

  std::cout << "Name: ";
  std::cout << searchResult.item->getName() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  lib::trim(line);
  if (line != "") {
    searchResult.item->setName(line);
  }

  std::cout << "Address: ";
  std::cout << searchResult.item->getAddress() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  lib::trim(line);
  if (line != "") {
    searchResult.item->setAddress(line);
  }

  // NOTE: type schould never change
  /*
  std::cout << "Type: ";
  std::cout << searchResult.item->getType() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "") {
    searchResult.item->setType(line[0]);
  }
  */

  if (searchResult.item->getType() == 'b') {
    Company *company = dynamic_cast<Company *>(searchResult.item);

    std::cout << "VAT: ";
    std::getline(std::cin, line);
    lib::trim(line);
    if (line != "") {
      company->setVAT(line);
    }

    std::cout << "Volume discount: ";
    std::getline(std::cin, line);
    lib::trim(line);
    if (line != "" && lib::stringIsInt(line)) {
      company->setVolumeDiscount(std::stoi(line));
    }
  }
}

void actionAddCustomer(std::vector<Customer *> &customers) {
  std::string name, address;
  char type;

  std::cout << "Name: ";
  std::getline(std::cin, name);
  lib::trim(name);
  if (lib::checkIfExists(customers, name, &Customer::getName)) {
    std::cout << "That customer already exists!!!" << std::endl;
    return;
  }

  std::cout << "Address: ";
  std::getline(std::cin, address);
  lib::trim(address);

  std::cout << "Type (c: customer, b: company): ";
  std::cin >> type;

  if (type == 'b') {
    std::string vat;
    int64_t volumeDiscount;
    std::cin.ignore();

    std::cout << "VAT: ";
    std::getline(std::cin, vat);
    lib::trim(vat);

    std::cout << "Volume discount: ";
    std::cin >> volumeDiscount;

    Company *company = new Company(name, address, type, vat, volumeDiscount);
    customers.push_back(company);
  } else {
    Customer *customer = new Customer(name, address, type);
    customers.push_back(customer);
  }

  lib::cleanStdin();
}

void actionUpdateStock(std::vector<Article *> &articles) {

  std::string line;

  // SearchResult<Article> searchResult = search(articles, &Article::getName);
  lib::SearchResult<Article> searchResult = lib::searchArticle(articles);

  if (searchResult.item == NULL) {
    std::cout << "No matching items" << std::endl;
    return;
  }

  std::cout << "Leave blank if old value is correct" << std::endl;

  std::cout << "Stock: ";
  std::cout << searchResult.item->getStock() << std::endl;
  std::cout << "new: ";
  std::getline(std::cin, line);
  if (line != "" && lib::stringIsInt(line)) {
    searchResult.item->setStock(std::stoi(line));
  }
}

void actionAddArticle(std::vector<Article *> &articles) {
  std::string name, manufacturer;
  int64_t diameter, stock;
  char type;
  float price;

  std::cout << "Name: ";
  std::getline(std::cin, name);
  lib::trim(name);
  if (lib::checkIfExists(articles, name, &Article::getName)) {
    std::cout << "That article already exists!!!" << std::endl;
    return;
  }

  std::cout << "Manufacturer: ";
  std::getline(std::cin, manufacturer);
  lib::trim(manufacturer);

  std::cout << "Diameter: ";
  std::cin >> diameter;

  std::cout << "Type (t: tire, r: rim): ";
  std::cin >> type;

  std::cout << "Stock: ";
  std::cin >> stock;

  std::cout << "Price: ";
  std::cin >> price;

  if (type == 't') {
    int64_t width, height;
    std::string speedIndex;
    char season;

    std::cout << "Width";
    std::cin >> width;

    std::cout << "Stock: ";
    std::cin >> height;

    std::cout << "Speed index: ";
    std::cin >> speedIndex;

    std::cout << "season: ";
    std::cin >> season;

    Tire *tire = new Tire(name, manufacturer, stock, diameter, price, type,
                          width, height, speedIndex, season);
    articles.push_back(tire);
  } else if (type == 'r') {
    bool aluminium;
    std::string color;
    int64_t width;

    std::cout << "Aluminium: ";
    std::cin >> aluminium;

    std::cout << "color: ";
    std::cin >> color;
    lib::trim(color);

    std::cout << "width: ";
    std::cin >> width;

    Rim *rim = new Rim(name, manufacturer, stock, diameter, price, type,
                       aluminium, color, width);
    articles.push_back(rim);
  } else {
    // NOTE: Article is an abstract class
    // Article *article =
    //    new Article(name, manufacturer, stock, diameter, price, type);
    // articles.push_back(article);
  }

  lib::cleanStdin();
}

void actionDeleteArticle(std::vector<Article *> &articles) {
  // SearchResult<Article> searchResult = search(articles, &Article::getName);
  lib::SearchResult<Article> searchResult = lib::searchArticle(articles);

  if (searchResult.item == NULL) {
    std::cout << "No matching items" << std::endl;
    return;
  }

  deleteFromVec(articles, searchResult, &Article::show);
}

void actionDeleteCustomer(std::vector<Customer *> &customers) {
  // SearchResult<Customer> searchResult = search(customers,
  // &Customer::getName);
  lib::SearchResult<Customer> searchResult = lib::searchCustomer(customers);

  if (searchResult.item == NULL) {
    std::cout << "No matching items" << std::endl;
    return;
  }

  deleteFromVec(customers, searchResult, &Customer::show);
}

} // namespace action
