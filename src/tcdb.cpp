#include "tcdb.hpp"

#include <cstring>
#include <iostream>

#include "article.hpp"
#include "company.hpp"
#include "customer.hpp"
#include "invoice.hpp"
#include "rim.hpp"
#include "tire.hpp"
#include "tirecenter.hpp"

namespace tcdb {
void load(TireCenter &tireCenter, std::string inFileName) {
  // 1 byte extra
  char buffer[9];

  std::ifstream ifile{inFileName, std::ios::out | std::ios::binary};

  // Check magic bytes
  ifile.read(buffer, 8);
  if (strcmp(buffer, VERSION)) {
    // TODO: Error handling
    exit(1);
  }

  _::loadTireCenter(tireCenter, ifile);

  ifile.close();
}

void save(TireCenter &tireCenter, std::string outFileName) {
  std::ofstream ofile{outFileName, std::ios::out | std::ios::binary};

  // Write magic bytes
  ofile << VERSION;

  // Save TireCenter and trickle down
  _::saveTireCenter(tireCenter, ofile);

  // Close file
  ofile.close();
}

namespace _ {

void loadTireCenter(TireCenter &tireCenter, std::ifstream &ifile) {
  std::string lineBuffer;

  // Read and set `name`
  std::getline(ifile, lineBuffer, '\0');
  tireCenter.setName(lineBuffer);

  // Read and set `address`
  std::getline(ifile, lineBuffer, '\0');
  tireCenter.setAddress(lineBuffer);

  loadArticles(tireCenter.getArticlesRef(), ifile);
  loadCustomers(tireCenter.getCustomersRef(), ifile);
  loadInvoices(tireCenter.getInvoicesRef(), ifile);
}

void saveTireCenter(TireCenter &tireCenter, std::ofstream &ofile) {
  // Save `name` & `address`
  ofile << tireCenter.getName().data() << '\0' << tireCenter.getAddress().data()
        << '\0';

  // Save `articles`
  saveArticles(tireCenter.getArticlesRef(), ofile);

  // Save `customers`
  saveCustomers(tireCenter.getCustomersRef(), ofile);

  // Save `Invoices`
  saveInvoices(tireCenter.getInvoicesRef(), ofile);
}

void loadArticles(std::vector<Article *> &articles, std::ifstream &ifile) {
  int64_t articlesCount;

  // Read articlesCount
  ifile.read((char *)&articlesCount, sizeof(int64_t));

  // Clear vector
  for (Article *article : articles) {
    delete article;
  }
  articles.clear();
  articles.reserve(articlesCount);

  // Load all articles
  for (int64_t ii = 0; ii < articlesCount; ii++) {
    Article *article = loadArticle(ifile);
    articles.push_back(article);
  }
}

void saveArticles(std::vector<Article *> &articles, std::ofstream &ofile) {
  // Write the amount of articles that are going to be stored
  int64_t articleCount = articles.size();
  ofile.write((char *)&articleCount, sizeof(int64_t));
  for (Article *article : articles) {
    saveArticle(article, ofile);
  }
}

void loadCustomers(std::vector<Customer *> &customers, std::ifstream &ifile) {
  int64_t customerCount;

  // Read articlesCount
  ifile.read((char *)&customerCount, sizeof(int64_t));

  // Clear vector
  for (Customer *customer : customers) {
    delete customer;
  }
  customers.clear();
  customers.reserve(customerCount);

  // Load all customers
  for (int64_t ii = 0; ii < customerCount; ii++) {
    Customer *customer = loadCustomer(ifile);
    customers.push_back(customer);
  }
}

void saveCustomers(std::vector<Customer *> &customers, std::ofstream &ofile) {
  int64_t customerCount = customers.size();
  ofile.write((char *)&customerCount, sizeof(int64_t));
  for (Customer *customer : customers) {
    saveCustomer(customer, ofile);
  }
}

void loadInvoices(std::vector<Invoice *> &invoices, std::ifstream &ifile) {
  int64_t invoiceCount;

  // Read invoiceCount
  ifile.read((char *)&invoiceCount, sizeof(int64_t));

  // Clear vector
  for (Invoice *invoice : invoices) {
    delete invoice;
  }
  invoices.clear();
  invoices.reserve(invoiceCount);

  // Load all invoices
  for (int64_t ii = 0; ii < invoiceCount; ii++) {
    Invoice *invoice = loadInvoice(ifile);
    invoices.push_back(invoice);
  }
}

void saveInvoices(std::vector<Invoice *> &invoices, std::ofstream &ofile) {
  int64_t invoiceCount = invoices.size();
  ofile.write((char *)&invoiceCount, sizeof(int64_t));
  for (Invoice *invoice : invoices) {
    saveInvoice(invoice, ofile);
  }
}

Article *loadArticle(std::ifstream &ifile) {
  std::string name;
  std::string manufacturer;
  int64_t stock, diameter;
  float price;
  char type;

  std::getline(ifile, name, '\0');
  std::getline(ifile, manufacturer, '\0');
  ifile.read((char *)&stock, sizeof(int64_t));
  ifile.read((char *)&diameter, sizeof(int64_t));
  ifile.read((char *)&price, sizeof(float));
  ifile.read((char *)&type, sizeof(char));

  if (type == 't') {
    int64_t width, height;
    std::string speedIndex;
    char season;

    ifile.read((char *)&width, sizeof(int64_t));
    ifile.read((char *)&height, sizeof(int64_t));
    std::getline(ifile, speedIndex, '\0');
    ifile.read((char *)&season, sizeof(char));

    Tire *tire = new Tire(name, manufacturer, stock, diameter, price, type,
                          width, height, speedIndex, season);
    return tire;
  } else if (type == 'r') {

    bool aluminium;
    std::string color;
    int64_t width;

    ifile.read((char *)&aluminium, sizeof(bool));
    std::getline(ifile, color, '\0');
    ifile.read((char *)&width, sizeof(width));

    Rim *tire = new Rim(name, manufacturer, stock, diameter, price, type,
                        aluminium, color, width);
    return tire;
  } else {
    // Weird type
    Article *article =
        new Article(name, manufacturer, stock, diameter, price, type);
    return article;
  }
}

void saveArticle(Article *article, std::ofstream &ofile) {
  int64_t stock = article->getStock();
  int64_t diameter = article->getDiameter();
  float price = article->getPrice();
  char type = article->getType();

  ofile << article->getName().data() << '\0'
        << article->getManufacturer().data() << '\0';

  ofile.write((char *)&stock, sizeof(int64_t));
  ofile.write((char *)&diameter, sizeof(int64_t));
  ofile.write((char *)&price, sizeof(float));
  ofile << type;

  if (type == 't') {
    Tire *tire = dynamic_cast<Tire *>(article);

    int64_t width = tire->getWidth();
    int64_t height = tire->getHeight();

    ofile.write((char *)&width, sizeof(int64_t));
    ofile.write((char *)&height, sizeof(int64_t));
    ofile << tire->getSpeedIndex().data() << '\0' << tire->getSeason();

  } else if (type == 'r') {
    Rim *rim = dynamic_cast<Rim *>(article);

    bool aluminium = rim->getAluminium();
    int64_t width = rim->getWidth();

    ofile.write((char *)&aluminium, sizeof(bool));
    ofile << rim->getColor().data() << '\0';
    ofile.write((char *)&width, sizeof(int64_t));
  } else {
    // Weird type
  }
}

Customer *loadCustomer(std::ifstream &ifile) {
  std::string name;
  std::string address;
  char type;

  std::getline(ifile, name, '\0');
  std::getline(ifile, address, '\0');
  ifile.read((char *)&type, sizeof(char));

  if (type == 'b') {
    std::string vat;
    int64_t volumeDiscount;

    std::getline(ifile, vat, '\0');
    ifile.read((char *)&volumeDiscount, sizeof(int64_t));

    Company *company = new Company(name, address, type, vat, volumeDiscount);
    return company;
  } else {
    Customer *customer = new Customer(name, address, type);
    return customer;
  }
}

void saveCustomer(Customer *customer, std::ofstream &ofile) {
  char type = customer->getType();

  ofile << customer->getName().data() << '\0' << customer->getAddress().data()
        << '\0' << type;

  if (type == 'b') {
    Company *company = dynamic_cast<Company *>(customer);
    int64_t volumeDiscount = company->getVolumeDiscount();

    ofile << company->getVAT().data() << '\0';
    ofile.write((char *)&volumeDiscount, sizeof(int64_t));
  }
}

Invoice *loadInvoice(std::ifstream &ifile) {
  Invoice *invoice = new Invoice;

  // Load customer
  Customer *customer_ptr = loadCustomer(ifile);
  Customer customer = *customer_ptr;
  delete customer_ptr;
  invoice->setCustomer(customer);

  // Load articles
  loadArticles(invoice->getArticlesAsRef(), ifile);

  // Load other values
  float price;
  int64_t discount;

  ifile.read((char *)&price, sizeof(float));
  ifile.read((char *)&discount, sizeof(discount));

  invoice->setPrice(price);
  invoice->setDiscount(discount);

  return invoice;
}

void saveInvoice(Invoice *invoice, std::ofstream &ofile) {
  Customer customer = invoice->getCustomer();
  float price = invoice->getPrice();
  int64_t discount = invoice->getDiscount();

  saveCustomer(&customer, ofile);
  saveArticles(invoice->getArticlesAsRef(), ofile);
  ofile.write((char *)&price, sizeof(float));
  ofile.write((char *)&discount, sizeof(int64_t));
}

} // namespace _

} // namespace tcdb
