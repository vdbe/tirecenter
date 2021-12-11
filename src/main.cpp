#include "main.hpp"

#include "action.hpp"
#include "article.hpp"
#include "company.hpp"
#include "rim.hpp"
#include "tcdb.hpp"
#include "tire.hpp"
#include "tirecenter.hpp"

#include <filesystem>
#include <iostream>
#include <vector>

void fill(TireCenter *, int);

int main(int argc, char **argv) {
  TireCenter tc;
  std::string file;

  // Get 'db' location
  if (argc > 1) {
    file = argv[1];
  } else {
    file = "test.tcdb";
  }

  // Check if it already exists
  // if so load it
  std::filesystem::path f{file};
  if (std::filesystem::exists(f)) {
    tcdb::load(tc, file);
  } else {
    tc.setName("Tire Center");
    tc.setAddress("The North Pole");
    fill(&tc, 20);
  }

  action::Action action;
  const action::UserType user = action::getUserType();

  std::vector<Customer *> &customers = tc.getCustomersRef();
  std::vector<Invoice *> &invoices = tc.getInvoicesRef();
  std::vector<Article *> &articles = tc.getArticlesRef();

  do {
    action = chooseAction(user);
    runAction(action, articles, customers, invoices);
  } while (action != action::Action::exitMenu);

  // Save 'db'
  tcdb::save(tc, file);
}

#include <sstream>
void fill(TireCenter *tc, int count) {
  {
    std::vector<Article *> articles(count);
    for (int64_t ii = 0; ii < count; ii++) {
      Tire *article = new Tire;
      std::ostringstream ss;

      ss << "article " << ii;
      article->setName(ss.str());

      ss.str("");
      ss.clear();
      ss << "manfacturer " << ii;

      article->setManufacturer(ss.str());

      article->setDiameter(ii);

      article->setType('t');

      article->setPrice(ii * 1.1);

      article->setStock(ii * ii);

      articles[ii] = article;
    }
    tc->setArticles(articles);
  }

  {
    std::vector<Customer *> customers(count);
    for (int ii = 0; ii < count; ii++) {
      Customer *customer = new Customer;
      std::ostringstream ss;

      ss << "customer " << ii;
      customer->setName(ss.str());

      ss.str("");
      ss.clear();
      ss << "street " << ii;
      customer->setAddress(ss.str());

      customer->setType('c');

      customers[ii] = customer;
    }
    tc->setCustomers(customers);
  }

  Company *company = new Company();
  company->setName("Company 1");
  company->setAddress("abc street 1");
  company->setVAT("abcd");
  company->setType('b');
  company->setVolumeDiscount(7);

  tc->addCustomer(company);

  // TODO: fill TireCenter::invoices
}
