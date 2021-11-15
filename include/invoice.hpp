#pragma once
#include <vector>

class Article;
// TODO: Figure out why this does not work!
// class Customer;

#include "customer.hpp"

class Invoice {
private:
  Customer customer;
  // TODO: Try to replace this with std::array<>
  std::vector<Article> articles;
  float price;
  int discount;

public:
  Customer getCustomer(void);
  void setCustomer(Customer);

  std::vector<Article> getArticles();
  void setArticles(std::vector<Article>);

  float getPrice(void);
  void setPrice(float);
  float calculatePrice(void);

  int getDiscount(void);
  void setDiscount(int);
  float calculateDiscount(void);
};
