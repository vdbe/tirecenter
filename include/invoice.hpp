#pragma once
#include <vector>

class Article;
class Customer;

class Invoice {
private:
  Customer *customer;
  // TODO: Try to replace this with std::array<>
  std::vector<Article *> articles;
  float price;
  int64_t discount;

public:
  Invoice();
  Invoice(Customer *, std::vector<Article *>, float, int64_t);
  ~Invoice();

  Customer *getCustomer(void) const;
  void setCustomer(Customer *);

  std::vector<Article *> getArticles() const;
  std::vector<Article *> &getArticlesAsRef();
  void setArticles(std::vector<Article *>);

  float getPrice(void) const;
  void setPrice(float);
  float calculatePrice(void);

  int64_t getDiscount(void) const;
  void setDiscount(int64_t);
  float calculateDiscount(void);

  void show(void) const;
};
