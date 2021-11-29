#include "action.hpp"
#include "article.hpp"
#include "company.hpp"
#include "invoice.hpp"
#include "tire.hpp"
#include "tirecenter.hpp"

#include <iostream>
#include <vector>

#include <functional>
void fill(TireCenter *, int);
#include <typeinfo>

int main() {
  TireCenter tc;
  Action action;

  std::vector<Article> &articles = tc.getArticlesRef();
  std::vector<Customer> &customers = tc.getCustomersRef();
  std::vector<Invoice> &invoices = tc.getInvoicesRef();
  fill(&tc, 20);

  Tire tire;
  tire.setManufacturer("tire");

  tire.setDiameter(10);

  tire.setType('a');

  tire.setPrice(11 * 1.1);

  tire.setStock(11 * 11);

  tire.setWidth(8);
  tire.setHeight(7);
  tire.setSpeedIndex("SPEED");
  tire.setSeason('S');
  articles.push_back(tire);

  tire.show();
  articles[0].show();

  const UserType user = getUserType();

  Company c;
  c.setName("test");

  do {
    action = chooseAction(user);
    runAction(action, articles, customers, invoices);
  } while (action != Action::exitMenu);

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
