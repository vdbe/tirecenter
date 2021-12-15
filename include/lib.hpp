#pragma once

#if !defined(DEFAULT_MAX_OPTIONS)
#define DEFAULT_MAX_OPTIONS 8
#endif

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Article;
class Customer;

namespace lib {

template <typename T> struct SearchResult {
  unsigned int index;
  T *item;
};

void cleanStdin(void);

bool stringIsInt(const std::string &);
bool stringIsFloat(const std::string &);

void ltrim(std::string &);
void rtrim(std::string &);
void trim(std::string &);

template <typename T>
SearchResult<T> search(std::vector<T *> &, std::string (T::*)(void) const);

template <typename T>
void deleteFromVec(std::vector<T *> &, SearchResult<T>,
                   void (T::*)(void) const);

size_t choose(char **, size_t, size_t);
void _draw_page(char **, size_t);

template <typename T>
void getCorrectSearchIndex(std::vector<T *> &, SearchResult<T> &);

SearchResult<Article> searchArticle(std::vector<Article *> &);
SearchResult<Customer> searchCustomer(std::vector<Customer *> &);

template <typename T, typename U>
bool checkIfExists(std::vector<T *>, U, U (T::*)(void) const);
} // namespace lib
