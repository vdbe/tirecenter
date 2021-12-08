#pragma once

#include <string>
#include <vector>

class TireCenter;
class Article;
class Invoice;
class Customer;

namespace tcdb {
[[maybe_unused]] const static char VERSION[] = "TCDB0001";

void load(TireCenter &, std::string);
void save(TireCenter &, std::string);

namespace _ {
void loadTireCenter(TireCenter &, std::ifstream &);
void saveTireCenter(TireCenter &, std::ofstream &);

void loadArticles(std::vector<Article *> &, std::ifstream &);
void saveArticles(std::vector<Article *> &, std::ofstream &);

void loadCustomers(std::vector<Customer *> &, std::ifstream &);
void saveCustomers(std::vector<Customer *> &, std::ofstream &);

void loadInvoices(std::vector<Invoice *> &, std::ifstream &);
void saveInvoices(std::vector<Invoice *> &, std::ofstream &);

Article *loadArticle(std::ifstream &);
void saveArticle(Article *, std::ofstream &);

Customer *loadCustomer(std::ifstream &);
void saveCustomer(Customer *, std::ofstream &);

Invoice *loadInvoice(std::ifstream &);
void saveInvoice(Invoice *, std::ofstream &);
} // namespace _
} // namespace tcdb
