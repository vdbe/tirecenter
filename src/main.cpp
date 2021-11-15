#include "article.hpp"
#include "tirecenter.hpp"

#include <iostream>
#include <vector>

void fill(TireCenter *, int);

int main() {
  TireCenter tc;
  fill(&tc, 20);

  // tc.test();

  // return 0;
  Action action;
  UserType user = TireCenter::getUserType();

  while ((action = TireCenter::chooseAction(user)) != Action::exitMenu) {
    tc.runAction(action);
  }

  return 0;
}

#include <sstream>
void fill(TireCenter *tc, int count) {
  {
    std::vector<Article> articles(count);
    for (int ii = 0; ii < count; ii++) {
      Article article;
      std::ostringstream ss;

      ss << "article " << ii;
      article.setName(ss.str());

      ss.str("");
      ss.clear();
      ss << "manfacturer " << ii;

      article.setManufacturer(ss.str());

      article.setDiameter(ii);

      article.setType(ii + 'a');

      article.setPrice(ii * 1.1);

      article.setStock(ii * ii);

      articles[ii] = article;
    }
    tc->setArticles(articles);
  }

  {
    std::vector<Customer> customers(count);
    for (int ii = 0; ii < count; ii++) {
      Customer customer;
      std::ostringstream ss;

      ss << "customer " << ii;
      customer.setName(ss.str());

      ss.str("");
      ss.clear();
      ss << "street " << ii;
      customer.setAddress(ss.str());

      customer.setType(ii + 'a');

      customers[ii] = customer;
    }
    tc->setCustomers(customers);
  }

  // TODO: fill TireCenter::invoices
}
