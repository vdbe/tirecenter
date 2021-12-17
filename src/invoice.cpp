#include <iostream>
#include <map>
#include <vector>

#include "article.hpp"
#include "company.hpp"
#include "customer.hpp"
#include "invoice.hpp"

Invoice::Invoice() {}
Invoice::Invoice(Customer *customer, std::vector<Article *> articles,
                 float price, int64_t discount)
    : customer(customer), articles(articles), price(price), discount(discount) {
}

Invoice::~Invoice() {
#ifdef PRINT_DESTRUCTORS
  std::cout << "Invoice::~Invoice()" << std::endl;
#endif
  delete this->customer;

  for (Article *article : this->articles) {
    delete article;
  }
}

Customer *Invoice::getCustomer(void) const { return this->customer; }

void Invoice::setCustomer(Customer *customer) { this->customer = customer; }

void Invoice::setArticles(std::vector<Article *> articles) {
  this->articles = articles;
}

std::vector<Article *> Invoice::getArticles(void) const {
  return this->articles;
}
std::vector<Article *> &Invoice::getArticlesAsRef(void) {
  return this->articles;
}

float Invoice::getPrice(void) const { return this->price; }

void Invoice::setPrice(float price) { this->price = price; }

float Invoice::calculatePrice() {
  float price = 0;

  for (auto article : this->articles) {
    price += article->getPrice() * article->getStock();
  }

  if (this->customer->getType() == 'c') {
    price *= 1.21;
  }

  this->price = price;

  return price;
}

int64_t Invoice::getDiscount(void) const { return this->discount; }

void Invoice::setDiscount(int64_t discount) { this->discount = discount; }

float Invoice::calculateDiscount() {
  char type = this->customer->getType();
  float discount = 0;

  if (type == 'b') {
    for (Article *article : this->articles) {
      Company *company = dynamic_cast<Company *>(this->customer);
      int64_t volumeDiscount = company->getVolumeDiscount();

      if (article->getStock() >= 10) {
        discount += (article->getPrice() + article->getStock()) *
                    (0.01 * volumeDiscount);
      }
    }
  } else if (type == 'c') {
    // Get Tire diameters
    std::map<int64_t, bool> diameters;
    for (Article *article : this->articles) {
      if (article->getType() == 't' && article->getStock() >= 4) {
        diameters[article->getDiameter()] = true;
      }
    }

    for (Article *article : this->articles) {
      if (article->getType() == 'r') {
        if (diameters.find(article->getDiameter()) != diameters.end() &&
            diameters[article->getDiameter() == true]) {
          diameters[article->getDiameter()] = false;
          discount += article->getPrice() * 0.1;
        }
      }
    }
    discount *= 1.21;
  }

  this->discount = discount;
  return discount;
}

void Invoice::show(void) const {
  std::cout << "=== Invoice ====" << std::endl;
  this->customer->show();
  for (Article *article : this->articles) {
    article->show();
  }
  std::cout << "Total price (discount included): "
            << this->getPrice() - this->getDiscount() << std::endl;
}
