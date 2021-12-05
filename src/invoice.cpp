#include <vector>

#include "article.hpp"
#include "customer.hpp"
#include "invoice.hpp"

Invoice::Invoice(){};
Invoice::Invoice(Customer customer, std::vector<Article *> articles,
                 float price, int discount)
    : customer(customer), articles(articles), price(price), discount(discount) {
}

Invoice::~Invoice() {
#ifdef PRINT_DESTRUCTORS
#include <iostream>
  std::cout << "Invoice::~Invoice()" << std::endl;
#endif
  for (Article *article : this->articles) {
    delete article;
  }
}

Customer Invoice::getCustomer(void) { return this->customer; }

void Invoice::setCustomer(Customer customer) { this->customer = customer; }

void Invoice::setArticles(std::vector<Article *> articles) {
  this->articles = articles;
}

std::vector<Article *> Invoice::getArticles(void) { return this->articles; }

float Invoice::getPrice(void) { return this->price; }

void Invoice::setPrice(float price) { this->price = price; }

float Invoice::calculatePrice() {
  float price = 0;

  for (auto article : this->articles) {
    price += article->getPrice();
  }

  this->price = price;

  return price;
}

int Invoice::getDiscount(void) { return this->discount; }

void Invoice::setDiscount(int discount) { this->discount = discount; }

float Invoice::calculateDiscount() {
  // TODO: Find out what this function is supposed to do
  return (float)this->discount;
}
