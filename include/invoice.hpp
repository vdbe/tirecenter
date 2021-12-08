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
  std::vector<Article *> articles;
  float price;
  int64_t discount;

public:
  Invoice();
  Invoice(Customer, std::vector<Article *>, float, int64_t);
  ~Invoice();

  Customer getCustomer(void);
  void setCustomer(Customer);

  std::vector<Article *> getArticles();
  std::vector<Article *> &getArticlesAsRef();
  void setArticles(std::vector<Article *>);

  float getPrice(void);
  void setPrice(float);
  float calculatePrice(void);

  int64_t getDiscount(void);
  void setDiscount(int64_t);
  float calculateDiscount(void);
};
